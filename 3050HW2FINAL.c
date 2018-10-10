//  Machine Problem 2
//  CS3050
//  Saab
//

/*
    Dylan Lade
    William Givens
    Claire Hough
*/

/*
    This program runs proportional to θ(|V| + |E|). First, the file reads in all of the vertices and inserts them into an array within our Vert struct. 
    This takes θ(|V|) time. Then, we send the array into our DFS algorithm, which is Kosaraju’s Algorithm. This has been proven to run in θ(|V| + |E|) time. 
    After the strongly connected components are determined, we use triple-nested loops like the example Professor Saab gave us in class to print out the non-duplicate 
    out-degrees of the SCC’s in linear time.  Thus, (|V|) + (|V| + |E|) = (2|V| + |E|) and since constants are dropped when determining θ time, our program runs in 
    θ(|V| + |E|) time, just as required.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERT  40

typedef struct{
    int visited;
    int magnitude;
    int adj[MAX_VERT];
} Vert;

typedef struct{
    int top;
    int elements[MAX_VERT];
} Stack;

typedef struct scc{
    int vList[MAX_VERT];
    int vMag;
    int adjList[MAX_VERT];
    int adjMag;
    int visited;
    int sccMag;
    struct scc* next;
} SCC;

void sccOut(SCC* sccList);
void sccDfs(int vertIndex, Vert vert[], SCC* scc);
void findSCC(Stack* stack, Vert vert[], int max, SCC* scc);
SCC* addSCC (SCC* head);
void buildArray(int s, int d, Vert* vert);
Stack* initializeStack (int max);
void stackDfs(int vertIndex, Vert vert[], Stack* stack, int max);
void pushStack(int vert, Stack* stack, int max);
void buildStack(int max, Vert vert[], Stack* stack);
void freeList (SCC* head);
void addAdjVert (SCC* scc, int vert);
int checkDuplicate (SCC* scc, int vert);


int main (int argc, char* argv[]) {

    //Check for input file
    if (argc != 2) {
        printf("Please Check input!\n");
        printf("Correct Input: ./a.out <inputFile>.txt\n");
        return 0;
    }

    char* inputFile = argv[1];
    int** input = malloc(sizeof(int*) * 6969);

    int max = 0 , index = 0;

    //Read in input file into input
    FILE *inptr = fopen(inputFile, "r");
    while (0 == 0) {
		if (feof(inptr)) break;

		*(input + index) = malloc(sizeof(int*));
		fscanf(inptr,"%d", *(input + index));

        //Calculate max number of vertices
        if (max < **(input + index)) max = **(input + index);

		++index;
	}

    //Initialize stack
    Stack* stack = initializeStack(max);

    //Initialize vertice array
    Vert vertices[max];
    for(int vertIndex = 0; vertIndex < max; vertIndex++){
        vertices[vertIndex].visited = 0;
        vertices[vertIndex].magnitude = 0;
        for(int adjIndex = 0; adjIndex < MAX_VERT; adjIndex++){
            vertices[vertIndex].adj[adjIndex] = ' ';
        }
    }

    //Populate vertice array
    index = 0;
    while((*(input+index)) != NULL){
        if(index == 0 || index % 2 == 0){
            int source = **(input+index);
            int dest = **(input+index+1);
            buildArray(source, dest, vertices);
        }
        index++;
    }
        
    //Translate vertices to stack
    buildStack(max, vertices, stack);
    
    //Find strongly connected components in graph 
    SCC* sccHead = addSCC (NULL);  
    findSCC(stack, vertices, max, sccHead);

    //Print out degree of the SCCs
    sccOut(sccHead);
    
    //Free memory
    fclose(inptr);
    free(input);
    free(stack);
    freeList(sccHead);
    
    return 0;
}


void sccDfs (int vertIndex, Vert vert[], SCC* scc) {
    int index, mag , adj;
    vert[vertIndex].visited = 1;
    for(index = 0, mag = vert[vertIndex].magnitude; index < mag; ++index){
        adj = vert[vertIndex].adj[index];

        if(adj > 0){
            if(!vert[adj-1].visited) sccDfs(adj-1, vert, scc);
            else addAdjVert(scc, adj);
        }
    }
   
    scc->vList[checkDuplicate(scc, vertIndex)] = (vertIndex + 1);
    scc->vMag += 1;
}


void findSCC (Stack* stack, Vert vert[], int max, SCC* sccList) {
    int vertIndex;

    while(stack->top > -1){
        vertIndex = stack->elements[stack->top--];
        if(!vert[vertIndex].visited){           
            sccDfs(vertIndex, vert, sccList);            
            sccList = addSCC(sccList);
        }
    }
}


void buildArray (int source, int dest, Vert* vert) {
   int index = 0;

   vert[source-1].magnitude++;
   vert[dest-1].magnitude++;

    while(vert[source-1].adj[index] != ' ') index++;
    vert[source-1].adj[index] = dest;

    index = 0;
    while(vert[dest-1].adj[index] != ' ') index++; 
    vert[dest-1].adj[index] = -source;
}


void pushStack (int vert, Stack* stack, int max) {
    stack->top++;
    if(stack->top < max) stack->elements[stack->top] = vert;
    else exit(1);
}


void stackDfs (int vertIndex, Vert vert[], Stack* stack, int max) {
    int index, mag , adj;
    vert[vertIndex].visited = 1;
    for(index = 0, mag = vert[vertIndex].magnitude; index < mag; ++index){
        adj = vert[vertIndex].adj[index]*(-1);

        if(adj > 0 && !vert[adj-1].visited) stackDfs(adj-1, vert, stack, max);
    }
	pushStack(vertIndex, stack, max);   
}


void buildStack (int max, Vert vert[], Stack* stack) {
    for(int index = 0; index < max; ++index){
        if(!vert[index].visited) stackDfs(index , vert, stack, max);
    }

    for(int i = 0; i < max; ++i) vert[i].visited = 0;
}


SCC* addSCC (SCC* head) {
    SCC* new;
    if(head == NULL) {
        head = malloc(sizeof(SCC));
        new = head;
    }
    else {
        SCC* temp = head;       
        while(temp->next != NULL) temp = temp->next;
        
        temp->next = malloc(sizeof(SCC));
        new = temp->next;
    }   
    
    new->next = NULL;
    new->sccMag = 0;
    new->vMag = 0;
    new->adjMag = 0;
    
    return new;
}


void sccOut (SCC* sccList) {
    int sccMag;

    SCC* REALhead = sccList;
    SCC* head = REALhead;
    while (sccList->next != NULL) {
        sccMag = 0;

        while (head->next != NULL) {
            int vertIndex = 0;
            while (vertIndex < head->vMag){
                for (int x = 0; x < sccList->adjMag; x++) {
                    if (head->vList[vertIndex] == sccList->adjList[x] && head->visited != 1) {
                        head->visited = 1;
                        sccMag++;                       
                    }    
                }
                vertIndex++;
            }
            head->visited = 0;
            head = head->next;
        }

        printf("%d ", sccMag);
        sccList = sccList->next;
        head = REALhead;
    }
    printf("\n");
}


void addAdjVert (SCC* scc, int vert) {
    int adjIndex = 0;
    while (adjIndex < scc->adjMag){
        if(scc->adjList[adjIndex] != vert) adjIndex++;
        else return;
    }

    scc->adjList[adjIndex] = vert;
    scc->adjMag += 1;
}


int checkDuplicate (SCC* scc, int vert) {
    int index = 0;
    int indexAdj = 0, arrayCounter = 0;
    while (index < scc->vMag){
        index++;
        while (indexAdj < scc->adjMag){
            if(scc->adjList[indexAdj] == vert+1) {                   
                while (arrayCounter < scc->adjMag) {
                    scc->adjList[arrayCounter] = scc->adjList[arrayCounter+1];
                    arrayCounter++;
                }
                scc->adjMag -= 1;
            }
            indexAdj++;
        }
    }
    return index;
}


Stack* initializeStack (int max) {
    Stack* stack = malloc(sizeof(Stack));
    stack->top = -1; 
    
    for(int stackIndex = 0; stackIndex < max + 1; stackIndex++){
      stack->elements[stackIndex]  = ' ';
    }
    return stack;
}


void freeList (SCC* vert) {
    SCC* current = vert;
    SCC* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    vert = NULL;
}
