#include <stdio.h>
#include <stdlib.h>

#define INFINITE 0x7FFFFFFF


int** graph;
int* parent;
int* costs;
int* visited;

unsigned int nodes;

void ReadGraph();
void PrintMatrix();
void Prim(int startNode);
int CalculateTree(int currentNode);
int GetMinPos();
void PrintTree(int currentNode);

int main()
{
    ReadGraph();
    PrintMatrix();
    Prim(9);
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
        graph[b][a] = c;
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

void Prim(int startNode){
    ///daca gaseste drum atunci printam drumul
    CalculateTree(startNode);
    PrintTree(startNode);
}
int CalculateTree(int currentNode){
    ///initializari vectori imporatanti
    parent = malloc(sizeof(int)*(nodes+1));
    visited = calloc(sizeof(int),nodes+1);
    costs = malloc(sizeof(int)*(nodes+1));

    int i;
    ///costuri initiale infinite peste tot
    for(i = 0; i <= nodes; i++)
        costs[i] = INFINITE,parent[i]=-1;

    ///nu ne costa nimic sa ajungem in pozitia initiala
    costs[currentNode] = 0;

    ///tatal nodului de inceput este 0
    parent[currentNode] = 0;
    int min;
    do{
        ///marcam nodul curent ca si vizitat
        visited[currentNode] = 1;
        ///updatam costurile vecinilor nodului curent
        for(i = 1; i <= nodes; i++)
            ///daca costul curent plus costul muchiei este mai mare && daca vecinul nu a fost vizitat
            ///&& exista muchie intre nod curent si nod vecin
            if(graph[currentNode][i]+costs[currentNode] < costs[i]
                && visited[i]==0 && graph[currentNode][i]!=INFINITE){
                costs[i] = costs[currentNode]+graph[currentNode][i];
                ///marcam nodul vecin ca si fiu al nodului curent
                parent[i]=currentNode;
            }
        ///aflam pozitia minimului pe care nu l-am vizitat
        min = GetMinPos();

        ///trecem la nodul minim
        currentNode = min;
    }while(currentNode > 0);///exista drum

    if(currentNode < 0)
        return 0;
    else return 1;
}

int GetMinPos(){
    int i;
    int min = INFINITE;
    int minPos = -1;
    for(i = 1; i <= nodes; i++){
        if(costs[i] < min && visited[i]==0)
        {
            min = costs[i];
            minPos = i;
        }
    }
    return minPos;
}
void PrintTree(int currentNode){
    int i;
    for(i = 1; i <= nodes; i++)
        printf("%d\t", i);
    printf("\n");
    for(i = 1; i <= nodes; i++)
        printf("%d\t", parent[i]);
}
