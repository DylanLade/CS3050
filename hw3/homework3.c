#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


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
    //struct Edge *adj; //(struct with integer index & weight)
    list_ptr adj, sorted_adj;
    //struct vert *next;
} vertex;


typedef struct{
    struct edge *edges;
    struct vert* vertices;
} Graph;

typedef struct q {
    int size;
    int heapMax;
    int* heap;
} *queuePtr, queue;




void parseInput (edgePtr edgeListHead,  vertex* vertices, int max); 
void mstPrim (vertex* vertices, int max);
int heapExtractMin(queuePtr queue);
void minHeapify (queuePtr queue, int index);

int main (int argc, char* argv[]) {

    //Check for input file
    if (argc != 2) {
        printf("Please Check input!\n");
        printf("Correct Input: ./a.out <inputFile>.txt\n");
        return 0;
    }

    char* inputFile = argv[1];
    //int** input = malloc(sizeof(int*) * 6969);
    edgePtr edgeListHead = malloc(sizeof(edge));
    //Graph* graph = malloc(sizeof(Graph));
    //graph->vertices = malloc(sizeof(Vert));
    
    //graph->edges = malloc(sizeof(Edge));
    //int input = 0;

    int max = 0;
    int index = 1;

    edgePtr tempEdge = edgeListHead;

    int input = 0;
    //Read in input file into input
    FILE *inptr = fopen(inputFile, "r");
    while (0 == 0) {
		if (feof(inptr)) {
			break;
		}
		// *(input + index) = malloc(sizeof(int*));
		// fscanf(inptr,"%d", *(input + index));
        // printf("%d\n", **(input + index));
        fscanf(inptr,"%d", &input);

        //fscanf(inptr,"%d", &input);

        // if (max < **(input + index)) {
        //     max = **(input + index);
        // }

        switch (index % 3) {
            case 1:
                tempEdge->src = input;
                if (max < input) max = input;
                
                break;

            case 2:
                tempEdge->dst = input;
                if (max < input) max = input;

                break;

            case 0:
                tempEdge->weight = input;
                tempEdge->next = malloc(sizeof(edge));
                printf("s:%d | d:%d | w:%d\n", tempEdge->src, tempEdge->dst, tempEdge->weight);
                tempEdge = tempEdge->next;
                break;

            default:
                printf("\nEdge error!\n");
                break;
        }

        //printf("%d", index);

		index++;
	}

    tempEdge->next = NULL;
    

    //lvert vertices;
    //graph->vertices = (vert*)malloc(sizeof(vert) * max);

    vertex vertices[max];
    max -= 1;
    vertex* G = vertices;

    // for (index = 0; index < max; index++) {
    //     vertices[index] = malloc(sizeof(vertex*));
    // }
    //printf("shit: %p\n", input);
    parseInput(edgeListHead, G, max);

    printf("%d", vertices[0].adj->name);


    printf("Max: %d", max);
    printf("\n");


    mstPrim(vertices, max);
}


void parseInput (edgePtr edgeListHead, vertex* vertices, int max) {
    int index = 0;
    //int vertIndex1 = 0;
    //int vertIndex2 = 0;

    int tempWeight = 0;

    //printf("shit: %p\n", input);

    //printf("shit: p:%p   |   v:%d\n", *(input+index), **(input+index));

    for (int vertArrayIndex = 0; vertArrayIndex <= max; vertArrayIndex++) {
        vertex tempVert = vertices[vertArrayIndex];
        printf("vI: %d\n", vertArrayIndex);
        list_ptr tempNeighbor = malloc(sizeof(list_el));
        tempNeighbor->next = NULL;

        vertices[vertArrayIndex].adj = tempNeighbor;
        printf("%p", vertices[vertArrayIndex].adj->next);
    }

    edgePtr tempEdge = edgeListHead;
    //int vertArrayIndex = 0
    // for (int vertArrayIndex = 0; vertArrayIndex < max; vertArrayIndex++) {
    //while(*(input+index) != NULL){
    while(tempEdge->next != NULL){
        printf("shit\n");
        //sleep(2);
        //int vertIndex1 = **(input + index);
        int vertIndex1 = tempEdge->src;
        printf("v:%d\n", vertIndex1);
        vertex tempVert1 = vertices[vertIndex1 - 1];        

        //int vertIndex2 = **(input + (index + 1));
        int vertIndex2 = tempEdge->dst;
        printf("v:%d\n", vertIndex2);
        vertex tempVert2 = vertices[vertIndex2 - 1];

        // tempWeight = **(input + (index + 2));
        tempWeight = tempEdge->weight;
        printf("w:%d\n", tempWeight);

        // if (tempVert1.adj == NULL) {
        //     tempVert1.adj = malloc(sizeof(list_ptr));
        //     printf("Making ADJ\n");
        // }

        printf("p:%p\n", vertices[vertIndex1 - 1].adj->next);
        printf("p:%p\n", tempVert1.adj->next);
        list_ptr tempNeighbor = tempVert1.adj;
        while (tempNeighbor->next != NULL) {
            printf("%p\n", tempNeighbor->next);
            tempNeighbor = tempNeighbor->next;

            printf("SHIT\n");
        }

        tempNeighbor->next = malloc(sizeof(list_ptr));
        tempNeighbor = tempNeighbor->next;
        tempNeighbor->name = vertIndex2;
        //printf("Nb: %d\n", tempNeighbor->name);
        tempNeighbor->weight = tempWeight;
        tempNeighbor->next = NULL;



        // if (tempVert2.adj == NULL) {
        //     tempVert2.adj = malloc(sizeof(list_ptr));
        // }

        tempNeighbor = tempVert2.adj;
        while (tempNeighbor->next != NULL) {
            tempNeighbor = tempNeighbor->next;
        }

        tempNeighbor->next = malloc(sizeof(list_ptr));
        tempNeighbor = tempNeighbor->next;
        tempNeighbor->name = vertIndex1;
        tempNeighbor->weight = tempWeight;
        tempNeighbor->next = NULL;

        printf("\n");

        index += 3;
        tempEdge = tempEdge->next;
    }    
}

void mstPrim (vertex* vertices, int max){
    //int A[max] = NULL;

    queuePtr queue = malloc(sizeof(queue));
    queue->size = max;
    queue->heapMax = max;
    int heap[max+1];
    int* heapPtr = heap;

    queue->heap = heapPtr;

    for (int vertIndex = 0; vertIndex <= max; vertIndex++){
        vertices[vertIndex].key = -1;
        vertices[vertIndex].onQueue = 1;
        heap[vertIndex] = vertIndex;
        //printf("Max: %d\n", max);
    }
    vertices[0].key = 0;

    // int A[max];
    // for (int index = 0; index <= ) 
    int mst = 0;
    for (int qSize = max; qSize >= 0; qSize--) {
        int u = heapExtractMin(queue);
        vertices[u].onQueue = 0;
        list_ptr tempNeighbor = vertices[u].adj;
        
        while (0==0) {
            if(vertices[tempNeighbor->name].onQueue == 1 && tempNeighbor->weight < vertices[tempNeighbor->name].key) {
                vertices[tempNeighbor->name].key = tempNeighbor->weight;
                printf("\nV: %d Weight %d\n", tempNeighbor->name, vertices[tempNeighbor->name].key);
            }

            if (tempNeighbor->next == NULL) {
                break;
            }
            else {
                tempNeighbor = tempNeighbor->next;
            }          
        }

        mst += vertices[u].key;        
    }

    printf("\n\nMST: %d\n", mst);

}


int heapExtractMin(queuePtr queue) {
    if (queue->size < 0) {
        printf("\nHeap underflow");
    }

    int startIndex = (queue->heapMax - queue->size);

    printf("Qsize: %d\n", queue->heapMax);
    printf("I: %d\n", startIndex);

    int max = queue->heap[startIndex];
    queue->heap[startIndex] = queue->heap[queue->heapMax];
    printf("\nmax: %d", max);

    queue->size -= 1;

    minHeapify(queue, startIndex);
    // for (int heapIndex = startIndex; heapIndex <= queue->size; heapIndex++) {
    //     break;
    // }

    return max;
}

void minHeapify (queuePtr queue, int index) {
    int left = index * 2;
    int right = (index * 2) + 1;

    int largest = 0;

    if (left <= queue->size && queue->heap[left] > queue->heap[index]) {
        largest = left;
    }
    else {
        largest = index;
    }

    if (right <= queue->size && queue->heap[right] > queue->heap[queue->heapMax]) {
        largest = right;
    }
   
    if (largest != index) {
        int temp = queue->heap[index];
        queue->heap[index] = queue->heap[queue->heapMax];
        queue->heap[queue->heapMax] = temp;
        minHeapify (queue, index);
    }
}
