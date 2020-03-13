#include <stdio.h>
#include <stdlib.h>

int** graph;
unsigned int nodes;
int* visited;

void ReadGraph();
void PrintMatrix();
void DFS(int start);

int main()
{
    ReadGraph();
    //PrintMatrix();
    DFS(4);
    return 0;
}

void ReadGraph(){
    FILE* input = fopen("graf.txt","r");
    unsigned int edges;
    fscanf(input,"%u %u", &nodes, &edges);

    ///aloca memorie pentru graf
    graph = malloc(sizeof(int)*(nodes+1));
    visited = calloc(sizeof(int),nodes+1);
    unsigned int i;

    for(i = 0; i <= nodes; i++){
        graph[i] = calloc(sizeof(int),nodes+1);
    }

    unsigned int a, b;

    for(i = 1; i <= edges; i++){
        fscanf(input, "%u %u", &a, &b);
        graph[a][b] = 1;
        graph[b][a] = 1;
    }
    fclose(input);
}

void PrintMatrix(){
    unsigned int i, j;
    for(i = 1; i <= nodes; i++){
        for(j = 1; j <= nodes; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}

void DFS(int start){
    ///TO DO: debug ca nu mere bine!!
    unsigned int i;
    printf("%d ", start);
    visited[start]=1;

    for(i = 1; i <= nodes; i++){
        if(graph[start][i]==1 && visited[i]==0)
            DFS(i);
    }
    return;
}
