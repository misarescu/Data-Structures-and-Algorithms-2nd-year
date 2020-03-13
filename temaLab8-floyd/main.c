#include <stdio.h>
#include <stdlib.h>
#define INFINITE 0x7FFFFFFF

int** graph;

unsigned int nodes;

void ReadGraph();
void PrintMatrix();
void Floyd();

int main()
{
    ReadGraph();
    Floyd();
    PrintMatrix();
    return 0;
}


void ReadGraph(){
    FILE* input = fopen("graf.txt","r");
    fscanf(input,"%u", &nodes);

    ///aloca memorie pentru graf
    graph = malloc(sizeof(int)*(nodes+1));
    unsigned int i, j;

    for(i = 0; i <= nodes; i++){
        graph[i] = malloc(sizeof(int)*(nodes+1));
        for(j = 0; j <= nodes; j++)
            graph[i][j] = INFINITE;
    }

    for(i = 0; i <= nodes; i++)
        graph[i][i] = 0;

    int a, b, c;

    while(fscanf(input, "%d %d %d", &a, &b, &c) == 3)
    {
        graph[a][b] = c;
    }
    fclose(input);
}

void PrintMatrix(){
    unsigned int i, j;
    for(i = 1; i <= nodes; i++){
        for(j = 1; j <= nodes; j++)
            if(graph[i][j] == INFINITE)
                fprintf(stdout,"INF\t");
            else
                fprintf(stdout,"%d\t", graph[i][j]);
        fprintf(stdout,"\n");
    }
}

void Floyd(){
    int i,j,k;
    for(k = 1; k <= nodes; k++)
        for(i = 1; i <= nodes; i++)
            for(j = 1; j <= nodes; j++)
                ///daca drumul direct [i,j] este mai mare decat drumul ocolitor prin k -> [i,k,j]
                ///atunci o luam pe drumul ocolitor
                if(graph[i][j] > graph[i][k] + graph[k][j] && graph[i][k] != INFINITE && graph[k][j]!=INFINITE)
                    graph[i][j] = graph[i][k] + graph[k][j];
}
