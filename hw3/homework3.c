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
    vertex vertices[max+1];

    vertex* verticesPtr = vertices;

    parseInput(edgeListHead, verticesPtr, max);

    mstPrim(vertices, max, maxWeight);

    printf("\nCalls: %d\n", calls);
    printf("MST: %d\n\n", mst);
}


void parseInput (edgePtr edgeListHead, vertex* vertices, int max) {
    int vertIndex1   = 0;
    int vertIndex2   = 0;
    int tempWeight   = 0;
    edgePtr tempEdge = edgeListHead;

    vertices[0].key = max;

    for (int vertArrayIndex = 1; vertArrayIndex < max; vertArrayIndex++) {
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

    for (int heapIndex = 1; heapIndex <= queue->size; heapIndex++) {
        heap[heapIndex] = heapIndex;
    }

    for (int vertIndex = 1; vertIndex <= max; vertIndex++) {
        vertices[vertIndex].key     = maxWeight + 1;
        vertices[vertIndex].onQueue = vertIndex;
    }

    // printHeap(vertices, queue, max);
    printHeap(vertices, queue, max);

    vertices[1].key = 0;

    while (queue->size > 1) {
        int u = heapExtractMin(vertices, queue);
        //u -= 1;
        //mst += vertices[u].key;
        //mst += u;
        //printf("\nKEY: %d\n", vertices[u].key);
        // vertices[u].onQueue = 0;


        
        if(vertices[u].adj != NULL){
            list_ptr tempNeighbor = vertices[u].adj;
            // printHeap(vertices, queue, max);
            while ( tempNeighbor != NULL ) {
                int neighborIndex = tempNeighbor->name;
                //neighborIndex -= 1;
                //printf("n:%d \n", neighborIndex);

                // if (vertices[u].key == vertices[neighborIndex].key) {
                //     if (neighborIndex > u) neighborIndex = u;
                    
                // }
                // onQueue -> index or V on heap
                //printf("\nshit\n");
                printf("Q:%d W:%d K:%d\n", vertices[neighborIndex].onQueue, tempNeighbor->weight, vertices[neighborIndex].key);
                if (vertices[neighborIndex].onQueue > 0 && tempNeighbor->weight < vertices[neighborIndex].key) {
                    vertices[neighborIndex].key = tempNeighbor->weight;
                    printf("\nSHIT\n");
                    // heapDecreaseKey(queue, queue->size, vertices[neighborIndex].key);       // heap decrease key for on queue  
                    // heapDecreaseKey(vertices, queue, neighborIndex, vertices[neighborIndex].key);  
                    heapDecreaseKey(vertices, queue, vertices[neighborIndex].onQueue, tempNeighbor->weight);

                    printf("\nE: %d->%d Weight %d\n", u, neighborIndex, vertices[neighborIndex].key);
                }
                //printf("\nSHIT2\n");
                //mst += tempNeighbor->weight;
                tempNeighbor = tempNeighbor->next;         
            }
            printHeap(vertices, queue, max);
        }
        mst += vertices[u].key;
        printf("\n");   
    }
}


void printHeap (vertex* vertices, queuePtr queue, int max) {
    printf("Size:%d | Q: ", queue->size);
    for (int arrIndex = 1; arrIndex <= queue->size; arrIndex++) {
    //for (int arrIndex = 1; arrIndex < max; arrIndex++) {
        // printf("%d - %d | ", queue->heap[arrIndex], vertices[queue->heap[arrIndex]].onQueue);
        printf("%d - %d | ", queue->heap[arrIndex], vertices[queue->heap[arrIndex]].key);
    }

    // printf("\nV: ");
    // for (int vertIndex = 1; vertIndex < max; vertIndex++) {
    //     printf("%d-%d | ", vertIndex+1, vertices[vertIndex].key);
    // }
    printf("\n");
}


int compare (vertex v[], int i, int j) {
    if ( (v[i].key < v[j].key ) || ((v[i].key == v[j].key) && (i<j)) )
        return 1;
    return 0;
}


void heapDecreaseKey (vertex* vertices, queuePtr queue, int index, int key) {
    //printf("index:%d  key:%d\n", index, key);
    if (key > vertices[queue->heap[index]].key) {
        printf("\nError new key is larger than current key | New:%d  Old:%d\n", key, vertices[index].key);
    }

    vertices[queue->heap[index]].key = key;

    int parent = (index / 2);

    //while (index > 1 && queue->heap[parent] > queue->heap[index]) {
    while (index > 1 && compare(vertices, vertices[index].onQueue, vertices[parent].onQueue)) {
        //if (compare(vertices, vertices[index].onQueue, vertices[parent].onQueue) == 1) {
            int temp             = queue->heap[index];
            queue->heap[index]   = queue->heap[parent];
            vertices[queue->heap[index]].onQueue = index;

            queue->heap[parent] = temp;
            vertices[queue->heap[parent]].onQueue = parent;

            // vertex tempVert = vertices[index];

            // vertices[index] = vertices[parent];
            // vertices[index].onQueue = index;

            // vertices[parent] = tempVert;
            // vertices[parent].onQueue = parent;
        //}
        index = parent;
        parent = parent / 2;
        
        
        //printf("INDEX:%d\n", index);
    }
}

// void heapDecreaseKey (vertex* vertices, queuePtr queue, int index, int key) {

//     int i = vertices[index].onQueue;

//     if (key > vertices[index].key) {
//         printf("\nError new key is larger than current key | New:%d  Old:%d\n", key, queue->heap[index-1]);
//     }

//     vertices[i].key = key;

//     while (index >= 0 && vertices[i].key < vertices[((i+1)/2)-1].key) {
//         queue->heap[i] = ((i+1)/2)-1;
//         queue->heap[((i+1)/2)-1] = i;

//         // int temp             = queue->heap[index-1];
//         // queue->heap[index-1] = queue->heap[((index+1)/2)-1];
//         // queue->heap[((index+1)/2)-1] = temp;
//         index = ((i+1)/2)-1;
//     }
// }

// void heapDecreaseKey (vertex* vertices, queuePtr queue, int index, int key) {
//     printf("index:%d  key:%d\n", index, key);
//     if (key > queue->heap[index]) {
//         printf("\nError new key is larger than current key | New:%d  Old:%d\n", key, queue->heap[index]);
//     }

//     queue->heap[index] = key;

//     while (index > 0 && queue->heap[((index+1)/2)-1] > queue->heap[index]) {
//         int temp           = queue->heap[index];
//         queue->heap[index] = queue->heap[((index+1)/2)-1];
//         queue->heap[((index+1)/2)-1] = temp;
//         index = ((index+1)/2)-1;
//         printf("INDEX:%d\n", index);
//     }
// }



int heapExtractMin (vertex* vertices, queuePtr queue) {
    if (queue->size < 1) {
        printf("\nHeap underflow");
    }

    int min = queue->heap[1];
    printf("min: %d\n", min);

    queue->heap[1] = queue->heap[queue->size];
    //vertices[queue->heap[1]].onQueue = 1;
    
    queue->size -= 1;

    minHeapify(vertices, queue, 1);

    return min;
}


void minHeapify (vertex* vertices, queuePtr queue, int index) {
    calls += 1;
    int left = index * 2;
    int right = (index * 2) + 1;

    int smallest = index;

    //if (left <= queue->size && queue->heap[left] < queue->heap[index]) {
    //if (left <= queue->size && compare(vertices, vertices[queue->heap[left]].onQueue, vertices[queue->heap[smallest]].onQueue) == 1) {
    if (left <= queue->size && compare(vertices, queue->heap[left], queue->heap[smallest])) {
        //if (compare(vertices, vertices[left].onQueue, vertices[smallest].onQueue) == 0) {
            smallest = left;
        //}
        
    }
    else {
        smallest = index;
    }

    //if (right <= queue->size && queue->heap[right] < queue->heap[smallest]) {
    //if (right <= queue->size && compare(vertices, vertices[queue->heap[right]].onQueue, vertices[queue->heap[smallest]].onQueue) == 1) {
    if (right <= queue->size && compare(vertices, queue->heap[right], queue->heap[smallest])) {
        //if (compare(vertices, vertices[right].onQueue, vertices[smallest].onQueue) == 0) {
            smallest = right;
        //}
    }
    
    if (smallest != index) {
        int temp              = queue->heap[index];
        
        queue->heap[index]    = queue->heap[smallest];
        vertices[queue->heap[index]].onQueue = index;
        //vertices[index].onQueue = index;

        queue->heap[smallest] = temp;
        vertices[queue->heap[smallest]].onQueue = smallest;
        //vertices[smallest].onQueue = smallest;


        // vertex tempVert = vertices[index];
        // vertices[index] = vertices[smallest];
        // vertices[smallest] = tempVert;
        printf("l:%d | r:%d\n", left, right);

        //vertices[queue->heap[index]].onQueue = index;         

        minHeapify(vertices, queue, smallest);
    }
}
