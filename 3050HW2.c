//  Machine Problem 2
//  CS3050
//  Saab
// 

/* 
    Dylan Lade 
    William Givens
    Claire Hough
*/

#include <stdio.h>
#include <stdlib.h>

void build_array(int** graph,int magnitude[], int check[], int max);

int main (int argc, char* argv[]) {

    //Check for input file
    if (argc != 2) {
        printf("Please Check input!\n");
        printf("Correct Input: ./a.out <inputFile>.txt\n");
        return 0;
    }

    char* inputFile = argv[1];
    int** input = malloc(sizeof(int*) * 6969);

    int max = 0;
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

    int magnitude[max];
    int check[max];
    for (int i = 0; i < max; i++) {
        magnitude[i] = 0;
        check[i] = 0;
    }
    build_array(input, magnitude, check, max);

    for(int i = 0; i < max; i++){
        if (check[i] == 1){
            printf("%d ", i);
        }
    }

    fclose(inptr);
    free(input);

    printf("\n");
    return 0;
}

void build_array (int** graph, int magnitude[], int check[], int max) {
    int index = 0;
    int temp;
    while(*(graph + index) != NULL){
        if(index == 0 || index % 2 == 0){
            temp =(**(graph + index));
            ++magnitude[temp - 1];
            check[magnitude[temp -1]] = 1;
        }
        ++index;
    }
}

/* New Program Flow:

    Build the graph and create the adjacency list
    search the graph for the SCC 
    turn the SCC into one component
    build the graph with that
    find the out degree of the SCC

*/