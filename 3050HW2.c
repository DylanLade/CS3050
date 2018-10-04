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

typedef struct{
    int visited;
    int magnitude;
    int adj[];
} Vert;

typedef struct{
    int top;
    int elements[];
} Stack;

void build_array(int** graph, Vert vert[], int max);
void push(int v, Stack s, int max);
int pop(Stack s);
void dfs(int v, int transpose, Vert vert[]);
void reset_visited(int max, Vert vert[]);
void order_pass(int max, Vert vert[]);
void scc_pass(Stack s, Vert vert[]);

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

    Vert vertices[max];
    Stack stack = {-1, {}};

    build_array(input, vertices, max);



    fclose(inptr);
    free(input);

    printf("\n");
    return 0;
}

void build_array (int** graph, Vert vert[], int max) {
    int index = 0, temp, dest, tempDest;
    for(int i = 0; i < max; i++){
        vert[i].adj[10 * max];
    }
    while(*(graph + index) != NULL){
        if(index == 0 || index % 2 == 0){
            temp = *(graph + index);
            dest = *(graph + (index + 1));
            vert[temp -1].magnitude++;
            int i = 0;
            while(vert[temp -1].adj[i] != NULL){
                tempDest = vert[temp - 1].adj[i];
                if(tempDest < dest){
                    
                }
            }
        }
    }
}

void push(int v, Stack s, int max){
    s.top++;
    if(s.top < max){
        s.elements[s.top] = v;
    } else{
        printf("Stack is full\n");
        exit(1);
    }
}

int pop(Stack s){
    return s.top < 0 ? -1 : s.elements[s.top--];
}

void dfs(int v, int transpose, Vert vert[]){
    int i, c ,n;
    vert[v].visited = 1;
    for(i = 0, c = vert[v].magnitude; i < c; ++i){
        n = vert[v].adj[i]*transpose;

        if(n > 0){
            if(!vert[n-1].visited){
                dfs(n-1, transpose, vert);
            }
        }
    }
}

void reset_visited(int max, Vert vert[]){
    for(int i = 0; i < max; ++i){
        vert[i].visited = 0;
    }
}

void order_pass(int max, Vert vert[]){
    for(int i = 0; i < max; ++i){
        if(!vert[i].visited){
            dfs(i , -1, vert);
        }
    }
}

void scc_pass(Stack s, Vert vert[]){
    int i = 0, v;
    while((v = pop(s)) != -1){
        if(!vert[v].visited){
            printf("scc %d", ++i);
            dfs(v, 1, vert);
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