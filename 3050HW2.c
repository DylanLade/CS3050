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
#include <string.h>

#define MAX_VERT  20

typedef struct{
    int visited;
    int magnitude;
    int adj[MAX_VERT];
} Vert;

typedef struct{
    int top;
    int elements[MAX_VERT];
} Stack;

void build_array(int s, int d, Vert* vert, int max);
void push(int v, Stack* stack, int max);
int pop(Stack* stack);
void dfs(int v, int transpose, Vert vert[], Stack* stack, int max);
void reset_visited(int max, Vert vert[]);
void order_pass(int max, Vert vert[], Stack* stack);
void scc_pass(Stack* stack, Vert vert[], int max);

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
    // printf("Max: %d", max);
    printf("\n");

    Vert vertices[max];
    Stack* stack = malloc(sizeof(stack));
    stack->top = -1;
   
    for(int i = 0; i <= max + 1; i++){
        stack->elements[i]  = ' ';
    }

    for(int i = 0; i < max; i++){
        vertices[i].visited = 0;
        vertices[i].magnitude = 0;
        for(int j = 0; j < MAX_VERT; j++){
            vertices[i].adj[j] = ' ';
        } 
    }

    index = 0;
    while((*(input+index)) != NULL){
        if(index == 0 || index % 2 == 0){
            int source = **(input+index);
            int dest = **(input+index+1);
            build_array(source, dest, vertices, max);
        }
        index++;
    }

    order_pass(max, vertices, stack);
    reset_visited(max, vertices);
    scc_pass(stack, vertices, max);

    fclose(inptr);
    free(input);

    // printf("\n");
    return 0;
}

void build_array (int s, int d, Vert* vert, int max) {
    int i = 0;
    int temp;
    vert[s-1].magnitude++;
    vert[d-1].magnitude++;
    while(vert[s-1].adj[i] != ' '){
      i++;
    }
    vert[s-1].adj[i] = d;

    int j = 0;
    while(vert[d-1].adj[j] != ' '){
        j++;
    }
    vert[d-1].adj[j] = -s;

}

void push(int v, Stack* stack, int max){
    stack->top++;
    if(stack->top < max){
        stack->elements[stack->top] = v;
    } else{
        printf("Stack is full\n");
        exit(1);
    }
}

int pop(Stack* stack){
    return stack->top < 0 ? -1 : stack->elements[stack->top--];
}

void dfs(int v, int transpose, Vert vert[], Stack* stack, int max){
    int i, c ,n;
    vert[v].visited = 1;
    for(i = 0, c = vert[v].magnitude; i < c; ++i){
        n = vert[v].adj[i]*transpose;

        if(n > 0){
            if(!vert[n-1].visited){
                dfs(n-1, transpose, vert, stack, max);
            }
        }
    }
    if (transpose < 0){
	    push(v, stack, max);
    } else{
	    printf("%d ", v + 1);
    }
}

void reset_visited(int max, Vert vert[]){
    for(int i = 0; i < max; ++i){
        vert[i].visited = 0;
    }
}

void order_pass(int max, Vert vert[], Stack* stack){
    for(int i = 0; i < max; ++i){
        if(!vert[i].visited){
            dfs(i , -1, vert, stack, max);
        }
    }
}

void scc_pass(Stack* stack, Vert vert[], int max){
    int i = 0, v;
    while((v = pop(stack)) != -1){
        // printf("SCC pass ");
        if(!vert[v].visited){
            printf("scc %d: ", ++i);
            dfs(v, 1, vert, stack, max);
            printf("\n");
        }
    }
}

/* New Program Flow:

    Build the graph and create the adjacency list
    search the graph for the SCC
    turn the SCC into one component
    build the graph with that
    find the out degree of the SCC

*/
