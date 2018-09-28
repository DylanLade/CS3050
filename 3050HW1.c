//  Machine Problem 1
//  CS3050
//  Saab
// September 24, 2018


/* 
    Dylan Lade 
    William Givens
    Claire Hough
*/

/*This program runs proportional to θ(|V| + |E|) by reading in the vertices of each edge in time proportional to V, 
and then sorting them in E time. It does this by reading in each vertex individually and putting them into an array. 
Then, each edge is considered as a pair of vertices and the values of each vertex are added to the other’s corresponding 
linked list (i.e. for edge (1, 2), “2” is inserted in Vertex 1’s linked list, and “1” is inserted in Vertex 2’s linked list). 
Since the vertices must be listed in ascending order, they must be sorted as they are being inserted. 
The worst-case time for sorting is 2E, the average time it takes to sort through all of the edges, which in this case would be 
having to check each value in a given Vertex’s linked list and eventually inserting the new node at the end of the linked list. 
This still preserves a time proportionality of V+2E = V+E because the constant is dropped. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Vertex structure
typedef struct vert {
    int v;
    struct vert* next;
} Vert;

void build_list (Vert** adjList, int v1, int v2, int max);
void freeList (Vert* vert);

int main (int argc, char* argv[]) {
    
    //Check for input file
    if (argc != 2) {
        printf("Please Check input!\n");
        printf("Correct Input: ./a.out <inputFile>.txt\n");
        return 0;
    }

    char* inputFile = argv[1];
    int** input     = malloc(sizeof(int*) * 6969);

    int max   = 0;
    int index = 0;


    //Read in input file into input
    FILE *inptr = fopen(inputFile, "r");
    while (0 == 0) {
		if (feof(inptr)) {
			break;
		}
		*(input + index) = malloc(sizeof(int*));
		fscanf(inptr,"%d", *(input + index));

        //Calculate max number of vertices
        if (max < **(input + index)) {
            max = **(input + index);
        }
		++index;
	}	

    //Create array based on max vertices
    Vert* adjList[max];
    for (index = 0; index < max; index++) {
        Vert* temp     = malloc(sizeof(Vert));
        temp -> v      = (-1 - index);
        temp -> next   = NULL;
        adjList[index] = temp;
    }

    //Sort vertice list into adjacency list
    index = 0;
    while (*(input + index) != NULL) {
        if (index == 0 || (index % 2) == 0) {
            int v1 = **(input + index );
            int v2 = **(input + index + 1);
            build_list(adjList, v1, v2, max);
        }
        ++index;
    }

    //Print out sorted adjacency list
    for (index = 0; index < max; index++) {
        Vert* temp  = adjList[index];
        Vert* vHead = adjList[index];

        printf("%d : ", (adjList[index]->v * (-1)));

        while (vHead -> next != NULL) {
            vHead = vHead -> next;
            printf("%d  ", vHead -> v);
        } 
        
        printf("\n");
    }

    //Free memory used by adjacency list
    for (index = 0; index < max; index++) {
        freeList(adjList[index]);
        adjList[index] = NULL;
    }

    //Free file pointer
    fclose(inptr);

    //Free input vertex list
    free(input);

    return 0;
}

void build_list (Vert** adjList, int v1, int v2, int max) {

    //Create struct for vertex 1
    Vert* tempVert1   = malloc(sizeof(Vert));
    tempVert1 -> v    = v2;
    tempVert1 -> next = NULL;

    //Create struct for vertex 2
    Vert* tempVert2   = malloc(sizeof(Vert));
    tempVert2 -> v    = v1;
    tempVert2 -> next = NULL;

    //Add v2 to adjacency list
    Vert* v1Head = adjList[v1-1];
    Vert* v1Prev;

    bool stop = false;
    if (v1Head -> v < 0 && v1Head->next == NULL) {
        v1Head -> next = tempVert1;
    } else {
        v1Prev = v1Head;
        v1Head = v1Head->next;
        while (v1Head -> next != NULL) {
            if (v1Head -> v > tempVert1 -> v && v1Head > 0) {
                tempVert1 -> next = v1Head;
                v1Prev -> next    = tempVert1;
                stop = true;
                break;
            }
            else {          
                v1Prev = v1Head;
                v1Head = v1Head -> next;
            }        
        }
        if (v1Head -> v > tempVert1 -> v && v1Head > 0) {
            tempVert1 -> next = v1Head;
            v1Prev -> next    = tempVert1;
            stop = true;
        }
        if (stop != true) {
            v1Head -> next = tempVert1;
        } 
    } 


    //Add v1 to adjacency list
    Vert* v2Head = adjList[v2-1];
    Vert* v2Prev;

    stop = false;
    if (v2Head -> v < 0 && v2Head->next == NULL) {
        v2Head -> next = tempVert2;
    } else {
        v2Prev = v2Head;
        v2Head = v2Head->next;
        while (v2Head -> next != NULL) {
            if (v2Head -> v > tempVert2 -> v && v2Head > 0) {
                tempVert2 -> next = v2Head;
                v2Prev -> next    = tempVert2;
                stop = true;
                break;
            }
            else {          
                v2Prev = v2Head;
                v2Head = v2Head -> next;
            }        
        }
        if (v2Head -> v > tempVert2 -> v && v2Head > 0) { 
            tempVert2 -> next = v2Head;
            v2Prev -> next    = tempVert2;
            stop = true;
        }
        if (stop != true) {
            v2Head -> next = tempVert2;
        } 
    }
}

void freeList (Vert* vert) {
    Vert* current = vert;
    Vert* next;

    while (current!= NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    vert = NULL;
}