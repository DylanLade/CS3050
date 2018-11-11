#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct edge {
    int index;
    int weight;
    struct edge *next;
} Edge;

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


void parseInput (int** input,  vertex* vertices, int max); 
void mstPrim (vertex* vertices, int max);
void heapExtractMin(int Array[]);

int main (int argc, char* argv[]) {

    //Check for input file
    if (argc != 2) {
        printf("Please Check input!\n");
        printf("Correct Input: ./a.out <inputFile>.txt\n");
        return 0;
    }

    char* inputFile = argv[1];
    int** input = malloc(sizeof(int*) * 6969);
    //Graph* graph = malloc(sizeof(Graph));
    //graph->vertices = malloc(sizeof(Vert));
    
    //graph->edges = malloc(sizeof(Edge));
    //int input = 0;

    int max = 0;
    int index = 0;

    //Edge* tempEdge = graph->edges;
    //Vert* tempVert = graph->vertices;

    //Read in input file into input
    FILE *inptr = fopen(inputFile, "r");
    while (0 == 0) {
		if (feof(inptr)) {
			break;
		}
		*(input + index) = malloc(sizeof(int*));
		fscanf(inptr,"%d", *(input + index));
        printf("%d\n", **(input + index));

        //fscanf(inptr,"%d", &input);

        if (max < **(input + index)) {
            max = **(input + index);
        }

        //printf("%d", index);

		index++;
	}

    

    //lvert vertices;
    //graph->vertices = (vert*)malloc(sizeof(vert) * max);

    vertex vertices[max];
    max -= 1;
    vertex* G = vertices;

    // for (index = 0; index < max; index++) {
    //     vertices[index] = malloc(sizeof(vertex*));
    // }
    printf("shit: %p\n", input);
    parseInput(input, G, max);

    printf("%d", vertices[0].adj->name);


    printf("Max: %d", max);
    printf("\n");
}


void parseInput (int** input, vertex* vertices, int max) {
    int index = 0;
    //int vertIndex1 = 0;
    //int vertIndex2 = 0;

    int tempWeight = 0;

    printf("shit: %p\n", input);

    printf("shit: p:%p   |   v:%d\n", *(input+index), **(input+index));

    for (int vertArrayIndex = 0; vertArrayIndex <= max; vertArrayIndex++) {
        vertex tempVert = vertices[vertArrayIndex];
        printf("vI: %d\n", vertArrayIndex);
        list_ptr tempNeighbor = malloc(sizeof(list_el));
        tempNeighbor->next = NULL;

        vertices[vertArrayIndex].adj = tempNeighbor;
        printf("%p", vertices[vertArrayIndex].adj->next);
    }

    
    //int vertArrayIndex = 0
    // for (int vertArrayIndex = 0; vertArrayIndex < max; vertArrayIndex++) {
    while(*(input+index) != NULL){
        printf("shit\n");
        //sleep(2);
        int vertIndex1 = **(input + index);
        printf("v:%d\n", vertIndex1);
        vertex tempVert1 = vertices[vertIndex1 - 1];        

        int vertIndex2 = **(input + (index + 1));
        printf("v:%d\n", vertIndex2);
        vertex tempVert2 = vertices[vertIndex2 - 1];

        tempWeight = **(input + (index + 2));
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
    }    
}

void mstPrim (vertex* vertices, int max){
    for (int vertIndex = 0; vertIndex <= max; vertIndex++){
        vertices[vertIndex].key = -1;
        vertices[vertIndex].onQueue = 1;
    }
    vertices[0].key = 0;

    for (int qSize = max; qSize >= 0; qSize--) {

    }

}


void heapExtractMin(int Heap[]) {

}