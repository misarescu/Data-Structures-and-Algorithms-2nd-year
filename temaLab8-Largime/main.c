#include <stdio.h>
#include <stdlib.h>

int** graph;
int* marked;
unsigned int nodes;

typedef struct node{
    int value;
    struct node* next;
}Node;

typedef struct list{
    Node* first;
    Node* last;
}List;

List queue;

void ReadGraph();
void PrintMatrix();
void Add(int value);
void Delete();
int Empty();
void BFS(int startNode);
int GetFirst();

int main()
{
    ReadGraph();
    PrintMatrix();
    BFS(1);
    return 0;
}

void ReadGraph(){
    FILE* input = fopen("graf.txt","r");
    fscanf(input,"%u", &nodes);

    ///aloca memorie pentru graf
    graph = malloc(sizeof(int)*(nodes+1));
    marked = calloc(sizeof(int),nodes+1);
    unsigned int i, j;

    for(i = 0; i <= nodes; i++){
        graph[i] = calloc(sizeof(int),(nodes+1));
    }

    int a, b;

    while(fscanf(input, "%d %d", &a, &b)==2)
    {
        graph[a][b] = 1;
        //graph[b][a] = 1;
    }
    fclose(input);
}

void PrintMatrix(){
    unsigned int i, j;
    for(i = 1; i <= nodes; i++){
        for(j = 1; j <= nodes; j++)
            fprintf(stdout,"%d\t", graph[i][j]);
        fprintf(stdout,"\n");
    }
}

void Add(int value){
    Node* new_Node = malloc(sizeof(Node));
    new_Node->value = value;
    new_Node->next=NULL;
    if(queue.first == NULL){
        queue.first = new_Node;
        queue.last = new_Node;
    }
    else{
        queue.last->next = new_Node;
        queue.last = new_Node;
    }
}

void Delete(){
    if(queue.first == NULL){
        printf("\nalready empty\n");
        system("pause");
    }
    else{
        struct Node* old_First = queue.first;
        queue.first = queue.first->next;
        free(old_First);
    }
}

int Empty(){
    if(queue.first == NULL)
        return 1;
    return 0;
}
void BFS(int startNode){
    Add(startNode);
    int i;
    int currentNode;
    marked[startNode]=1;
    while(!Empty()){
        currentNode = GetFirst();
        for(i = 1; i <=nodes; i++){
            if(graph[currentNode][i] == 1 && marked[i] == 0){
                Add(i);
                marked[i]=1;
            }
        }
        printf("%d ", currentNode);
        Delete();
    }
}

int GetFirst(){
    if(queue.first != NULL)
        return queue.first->value;
    else return -1;
}
