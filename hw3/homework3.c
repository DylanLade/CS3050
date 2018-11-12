#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct e {
    int src;
    int dst;
    int weight;
    struct e *next;
} edge, *edgePtr;

typedef struct s { /* this is the structure for bulding list of neighbors*/
int name;
int weight;
struct s *next;
} list_el, *list_ptr;

typedef struct v {
    int key;
    int onQueue;
    list_ptr adj, sorted_adj;
} vertex;

typedef struct q {
    int size;
    int* heap;
} *queuePtr, queue;


void parseInput (edgePtr edgeListHead,  vertex* vertices, int max); 
void mstPrim (vertex* vertices, int max, int maxWeight);
int heapExtractMin(queuePtr queue);
void minHeapify (queuePtr queue, int index);
void insertVert (vertex* vertices, int vertIndex, int adjIndex, int weight);
void heapDecreaseKey (queuePtr queue, int index, int key); 
int compare(vertex v[], int i, int j); 
void printHeap (queuePtr queue, int max);

int calls = 0;
int mst = 0;


int main (int argc, char* argv[]) {

    //Check for input file
    if (argc != 2) {
        printf("Please Check input!\n");
        printf("Correct Input: ./a.out <inputFile>.txt\n");
        return 0;
    }

    char* inputFile = argv[1];

    int max = 0;
    int maxWeight = 0;
    int index = 3;

    edgePtr edgeListHead = malloc(sizeof(edge));
    edgePtr tempEdge = edgeListHead;

    int input = 0;
    //Read in input file into input
    FILE *inptr = fopen(inputFile, "r");
    while (0 == 0) {
		if (feof(inptr)) {
			break;
		}

        fscanf(inptr,"%d", &input);

        switch (index % 3) {
            case 0:
                tempEdge->src = input;
                if (max <= tempEdge->src) max = tempEdge->src;              
                break;

            case 1:
                tempEdge->dst = input;
                if (max <= tempEdge->dst) max = tempEdge->dst;
                break;

            case 2:
                if (maxWeight <= input) maxWeight = input;

                tempEdge->weight = input;
                tempEdge->next = malloc(sizeof(edge));
                printf("s:%d | d:%d | w:%d\n", tempEdge->src, tempEdge->dst, tempEdge->weight);
                tempEdge = tempEdge->next;
                break;

            default:
                printf("\nEdge error!\n");
                break;
        }
        index += 1;
	}

    tempEdge->next = NULL;

    printf("MaxV: %d  |  MaxW: %d\n", max, maxWeight);
    max+=1;
    vertex vertices[max];

    vertex* verticesPtr = vertices;

    parseInput(edgeListHead, verticesPtr, max);

    mstPrim(vertices, max, maxWeight);

    printf("\nCalls: %d\n", calls);
    printf("MST: %d\n\n", mst);
}


void parseInput (edgePtr edgeListHead, vertex* vertices, int max) {
    int vertIndex1 = 0;
    int vertIndex2 = 0;
    int tempWeight = 0;
    edgePtr tempEdge = edgeListHead;

    for (int vertArrayIndex = 1; vertArrayIndex <= max; vertArrayIndex++) {
        vertex tempVert = vertices[vertArrayIndex];
        vertices[vertArrayIndex].adj = NULL;
    }

    while(tempEdge->next != NULL){
        vertIndex1 = tempEdge->src;
        vertIndex2 = tempEdge->dst;
        tempWeight = tempEdge->weight;

        printf("v:%d | v:%d | w:%d\n", vertIndex1, vertIndex2, tempWeight);

        insertVert(vertices, vertIndex1, vertIndex2, tempWeight);
        insertVert(vertices, vertIndex2, vertIndex1, tempWeight);

        tempEdge = tempEdge->next;
    } 
}

void insertVert (vertex* vertices, int vertIndex, int adjIndex, int weight) {
    printf("Insert | V:%d | Adj:%d | W:%d\n", vertIndex, adjIndex, weight);

    vertex* tempVert = &vertices[vertIndex];

    list_ptr newNeighbor = malloc(sizeof(list_ptr));
    newNeighbor->next = NULL;
    newNeighbor->name = adjIndex;
    newNeighbor->weight = weight;   

    if (tempVert->adj == NULL || tempVert->adj->name >= newNeighbor->name) { 
        newNeighbor->next = tempVert->adj; 
        tempVert->adj = newNeighbor; 
    } 
    else { 
        list_ptr current = tempVert->adj; 
        while (current->next != NULL && current->next->name < newNeighbor->name) { 
            current = current->next; 
        } 
        newNeighbor->next = current->next; 
        current->next = newNeighbor; 
    }  
}


void mstPrim (vertex* vertices, int max, int maxWeight){
    printf("PRIM\n");

    queuePtr queue = malloc(sizeof(queue));
    queue->size = max;
    int heap[max];
    int* heapPtr = heap;
    queue->heap = heapPtr;

    for (int heapIndex = 1; heapIndex <= max; heapIndex++) {
        heap[heapIndex] = heapIndex;
    }

    for (int vertIndex = 1; vertIndex <= max; vertIndex++){
        vertices[vertIndex].key = maxWeight + 1;
        vertices[vertIndex].onQueue = 1;
    }

    printHeap(queue, max);

    vertices[1].key = 0;

    while (queue->size > 1){
        int u = heapExtractMin(queue);
        mst += vertices[u].key;
        printf("\nKEY: %d\n", vertices[u].key);
        vertices[u].onQueue = 0;

        list_ptr tempNeighbor = vertices[u].adj;
        
        printHeap(queue, max);
        while (tempNeighbor != NULL) {
            int neighborIndex = tempNeighbor->name;
            //printf("n:%d \n", neighborIndex);

            if (vertices[u].key == vertices[neighborIndex].key) {
                if (neighborIndex > u) neighborIndex = u;
                
            }

            if(vertices[neighborIndex].onQueue == 1 && tempNeighbor->weight < vertices[neighborIndex].key) {
                vertices[neighborIndex].key = tempNeighbor->weight;

                heapDecreaseKey(queue, queue->size, vertices[neighborIndex].key);        

                printf("\nV: %d Weight %d\n", neighborIndex, vertices[neighborIndex].key);

                //mst += tempNeighbor->weight;
            }

            //mst += tempNeighbor->weight;
            tempNeighbor = tempNeighbor->next;         
        }   
    }
}


void printHeap (queuePtr queue, int max) {
    for(int arrIndex = 1; arrIndex < queue->size; arrIndex++) {
        printf("%d ", queue->heap[arrIndex]);
    }
    printf("\n");
}


int compare (vertex v[], int i, int j) {
    if ( (v[i].key < v[j].key ) || ((v[i].key == v[j].key) && (i<j)) )
        return 1;
    return 0;
}


void heapDecreaseKey (queuePtr queue, int index, int key) {

    if (key > queue->heap[index]) {
        printf("\nError new key is larger than current key\n");
        printf("Key | New:%d  Old:%d\n", key, queue->heap[index]);
    }

    queue->heap[index] = key;

    while (index > 1 && queue->heap[index/2] > queue->heap[index]){
        int temp = queue->heap[index];
        queue->heap[index] = queue->heap[index/2];
        queue->heap[index/2] = temp;
        index--;
    }
}


int heapExtractMin (queuePtr queue) {
    if (queue->size < 1) {
        printf("\nHeap underflow");
    }
    printf("Qsize: %d\n", queue->size-1);

    int min = queue->heap[1];
    printf("\nmin: %d\n", min);

    queue->heap[1] = queue->heap[queue->size];
    
    queue->size -= 1;

    minHeapify(queue, 1);

    return min;
}


void minHeapify (queuePtr queue, int index) {
    calls += 1;
    // int left = ((index+1) * 2)-1;
    // int right = ((index+1) * 2);
    int left = index * 2;
    int right = (index * 2) + 1;
    printf("l:%d | r:%d\n", left, right);

    int smallest = 1;

    if (left <= queue->size && queue->heap[left] < queue->heap[index]) {
        smallest = left;
    }
    else {
        smallest = index;
    }

    if (right <= queue->size && queue->heap[right] < queue->heap[smallest]) {
        smallest = right;
    }
   
    if (smallest != index) {
        int temp = queue->heap[index];
        queue->heap[index] = queue->heap[smallest];
        queue->heap[smallest] = temp;
        minHeapify (queue, smallest);
    }
}
