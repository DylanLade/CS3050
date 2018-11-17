#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct e {
    int src;
    int dst;
    int weight;
    struct e *next;
} edge, *edgePtr;

typedef struct s {
int name;
int weight;
struct s *next;
} list_el, *list_ptr;

typedef struct v {
    int key;
    int name;
    int onQueue;
    list_ptr adj, sorted_adj;
} vertex;

typedef struct q {
    int size;
    int* heap;
} *queuePtr, queue;


void parseInput (edgePtr edgeListHead,  vertex* vertices, int max); 
void mstPrim (vertex* vertices, int max, int maxWeight);
int heapExtractMin(vertex* vertices, queuePtr queue);
void minHeapify (vertex* vertices, queuePtr queue, int index);
void insertVert (vertex* vertices, int vertIndex, int adjIndex, int weight);
void heapDecreaseKey (vertex* vertices, queuePtr queue, int index, int key); 
int compare(vertex v[], int i, int j); 
void printHeap (vertex* vertices,  queuePtr queue, int max);

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
    int index = 0;

    edgePtr edgeListHead = malloc(sizeof(edge));
    edgePtr tempEdge = edgeListHead;

    int src = 0;
    int dst = 0;
    int w = 0;
    //Read in input file into input
    FILE *inptr = fopen(inputFile, "r");
    while (0 == 0) {
		if (feof(inptr)) {
			break;
		}

        //fscanf(inptr,"%d", &input);
        fscanf(inptr, "%d %d %d\n", &src, &dst, &w);

        tempEdge->src = src;
        if (max <= tempEdge->src) max = tempEdge->src;              

        tempEdge->dst = dst;
        if (max <= tempEdge->dst) max = tempEdge->dst;

        if (maxWeight <= w) maxWeight = w;

        tempEdge->weight = w;
        tempEdge->next   = malloc(sizeof(edge));

        printf("s:%d | d:%d | w:%d\n", tempEdge->src, tempEdge->dst, tempEdge->weight);

        tempEdge = tempEdge->next;
	}

    tempEdge->next = NULL;

    printf("MaxV: %d  |  MaxW: %d\n", max, maxWeight);
    //max+=1;
    vertex vertices[max];

    vertex* verticesPtr = vertices;

    parseInput(edgeListHead, verticesPtr, max);

    mstPrim(vertices, max, maxWeight);

    //printf("MaxV: %d  |  MaxW: %d\n", max, maxWeight);

    printf("\nCalls: %d\n", calls);
    printf("MST: %d\n\n", mst);


}


void parseInput (edgePtr edgeListHead, vertex* vertices, int max) {
    int vertIndex1   = 0;
    int vertIndex2   = 0;
    int tempWeight   = 0;
    edgePtr tempEdge = edgeListHead;

    vertices[0].key = max;

    for (int vertArrayIndex = 1; vertArrayIndex <= max; vertArrayIndex++) {
        vertex tempVert = vertices[vertArrayIndex];
        tempVert.name = vertArrayIndex;
        vertices[vertArrayIndex].adj = NULL;
    }

    while (tempEdge->next != NULL) {
        vertIndex1 = tempEdge->src;
        vertIndex2 = tempEdge->dst;
        tempWeight = tempEdge->weight;

        insertVert(vertices, vertIndex1, vertIndex2, tempWeight);
        insertVert(vertices, vertIndex2, vertIndex1, tempWeight);

        tempEdge = tempEdge->next;
    } 
}


void insertVert (vertex* vertices, int vertIndex, int adjIndex, int weight) {
    //printf("Insert | V:%d | Adj:%d | W:%d\n", vertIndex, adjIndex, weight);

    vertex* tempVert = &vertices[vertIndex];

    list_ptr newNeighbor = malloc(sizeof(list_ptr));
    newNeighbor->next   = NULL;
    newNeighbor->name   = adjIndex;
    newNeighbor->weight = weight;   

    if (tempVert->adj == NULL || tempVert->adj->name >= newNeighbor->name) { 
        newNeighbor->next = tempVert->adj; 
        tempVert->adj     = newNeighbor; 
    } 
    else { 
        list_ptr current = tempVert->adj; 
        while (current->next != NULL && current->next->name < newNeighbor->name) { 
            current = current->next; 
        } 
        newNeighbor->next = current->next; 
        current->next     = newNeighbor; 
    }  
}


void mstPrim (vertex* vertices, int max, int maxWeight) { 
    printf("\nPRIM\n\n");

    queuePtr queue = malloc(sizeof(queue));
    int heap[max+1];
    int* heapPtr = heap;
    queue->heap  = heapPtr;
    queue->size  = max;

    vertices[0].key = queue->size;
    queue->heap[0] = maxWeight;

    for (int heapIndex = 1; heapIndex <= queue->size; heapIndex++) {
        heap[heapIndex] = heapIndex;
    }

    for (int vertIndex = 1; vertIndex <= max; vertIndex++) {
        vertices[vertIndex].key     = maxWeight + 1;
        vertices[vertIndex].onQueue = vertIndex;
    }  
    
    vertices[1].key = 0;

    while (queue->size > 0) {
        printHeap(vertices, queue, max);
        int u = heapExtractMin(vertices, queue);
        //printf("| U:%d  |\n", u);
        //mst += vertices[u].key;
        //printf("MST: %d\n", mst);
        

        if(vertices[u].adj != NULL){
            list_ptr tempNeighbor = vertices[u].adj;
            
            while ( tempNeighbor != NULL) {
                int neighborIndex = tempNeighbor->name;
                printf("NI:%d w:%d k:%d oQ:%d\n", neighborIndex, tempNeighbor->weight, vertices[neighborIndex].key, vertices[neighborIndex].onQueue);
                if (vertices[neighborIndex].onQueue > 0 && tempNeighbor->weight < vertices[neighborIndex].key) {
                    vertices[neighborIndex].key = tempNeighbor->weight;
                    heapDecreaseKey(vertices, queue, vertices[neighborIndex].onQueue, tempNeighbor->weight);

                    //printf("\n---|  E: %d->%d Weight %d\n", u, neighborIndex, vertices[neighborIndex].key);
                }
                //printf("\nE: %d->%d Weight %d\n", u, neighborIndex, vertices[neighborIndex].key);
                tempNeighbor = tempNeighbor->next;         
            }
            //printHeap(vertices, queue, max);
        }
        mst += vertices[u].key;
        
        printf("\nMST: %d\n", mst);
        //printf("\n");   
    }
}


void printHeap (vertex* vertices, queuePtr queue, int max) {
    printf("Size:%d | Q: ", queue->size);
    for (int arrIndex = 1; arrIndex <= max; arrIndex++) {
        printf("v:%d w:%d oQ:%d | ", queue->heap[arrIndex], vertices[queue->heap[arrIndex]].key, vertices[queue->heap[arrIndex]].onQueue);
    }
    printf("\n");
    // for (int arrIndex = max - queue->size+1; arrIndex <= max; arrIndex++) {
    //     vertices[arrIndex].onQueue = 0;
    // }
}


int compare (vertex v[], int i, int j) {
    if ( (v[i].key < v[j].key ) || ((v[i].key == v[j].key) && (i<j)) )
        return 1;
    return 0;
}


void heapDecreaseKey (vertex* vertices, queuePtr queue, int index, int key) {
    printf("++ DKEY | index:%d  key:%d\n", index, key);
    if (key > vertices[queue->heap[index]].key) {
        printf("\nError new key is larger than current key | New:%d  Old:%d\n", key, vertices[index].key);
    }

    vertices[queue->heap[index]].key = key;

    int parent = (index / 2);

    // if (parent == 0) {
    //     parent = 1;
    //     index = 1;
    // }

    printf("\n++ DKEY1 | A:%d | I:%d | P:%d\n", queue->heap[parent], index, parent);
    while (index > 0 && compare(vertices, queue->heap[index], queue->heap[parent])) {
        printf("++ DKEYS | switching %d:%d and %d:%d\n",queue->heap[parent], vertices[queue->heap[parent]].key, queue->heap[index], vertices[queue->heap[index]].key);
        int temp             = queue->heap[index];
        queue->heap[index]   = queue->heap[parent];
        vertices[queue->heap[index]].onQueue = index;

        queue->heap[parent] = temp;
        vertices[queue->heap[parent]].onQueue = parent;

        index = parent;
        parent = parent / 2;

        //if (parent == 0) parent = 1;
    }
}


int heapExtractMin (vertex* vertices, queuePtr queue) {
    if (queue->size < 0) {
        printf("\nHeap underflow");
    }

    int min = queue->heap[1];
    
    vertices[min].onQueue = 0;
    

    queue->heap[1] = queue->heap[queue->size];
    
    vertices[0].key = queue->size;
    
    
    queue->size -= 1;

    minHeapify(vertices, queue, 1);
    printf("min: %d\n", min);

    return min;
}


void minHeapify (vertex* vertices, queuePtr queue, int index) {
    printf("\nf: %d\n", queue->size);
    calls += 1;

    if (queue->size != 1) {
        int left = index * 2;
        int right = (index * 2) + 1;

        int smallest = index;

        if (left <= queue->size && compare(vertices, queue->heap[left], queue->heap[smallest])) {
            printf("MH | L | left:%d   min:%d\n", left, smallest);
            smallest = left;
        }
        else {
            smallest = index;
        }

        if (right <= queue->size && compare(vertices, queue->heap[right], queue->heap[smallest])) {
            printf("MH | R | right:%d   min:%d\n", right, smallest);
            smallest = right;

        }
        
        if (smallest != index) {
            
            printf("switching %d:%d and %d:%d\n",queue->heap[smallest], vertices[queue->heap[smallest]].key, queue->heap[index], vertices[queue->heap[index]].key);
            int temp              = queue->heap[index];
            
            queue->heap[index]    = queue->heap[smallest];
            vertices[queue->heap[index]].onQueue = index;

            queue->heap[smallest] = temp;
            vertices[temp].onQueue = smallest;

            printf("l:%d | r:%d\n", left, right);      

            minHeapify(vertices, queue, smallest);
        }
    }
    // else if(queue->size == 2 && compare(vertices, queue->heap[2], queue->heap[1])){
    //     int temp              = queue->heap[1];
    //     printf("\n\nCCCCCCCCCCC\n");
    //     queue->heap[1]    = queue->heap[2];
    //     vertices[queue->heap[1]].onQueue = 1;

    //     queue->heap[2] = temp;
    //     vertices[temp].onQueue = 2;

    //     //printf("---| switching %d:%d and %d:%d\n",queue->heap[1], vertices[queue->heap[1]].key, queue->heap[2], vertices[queue->heap[2]].key);
    //     //printf("--| l:%d | r:%d |--\n", left, right);      

    //     minHeapify(vertices, queue, 1);
    // }
    else if(queue->size == 1){
        vertices[queue->heap[1]].onQueue = 1;
        //queue->heap[1] = queue->heap[2];
        //printf("---| switching %d:%d and %d:%d\n",queue->heap[2], vertices[queue->heap[2]].key, queue->heap[1], vertices[queue->heap[1]].key);
        //printf("--| l:%d | r:%d |--\n", left, right);      

        //minHeapify(vertices, queue, 1);
    }
}
