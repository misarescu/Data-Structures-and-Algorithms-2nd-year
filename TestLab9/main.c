///Subiectul 1
///se da un graf orientat cu n varfuri si m muchii, fara costuri titit prin
///vectorul muchiilor din fisierul GRAF.TXT. Sa se foloseasca algoritmul
///de explorare in largime pentru a afisa drumul cel mai scurt de la
///nodul s la nodul v. Noduile s si v se citesc de la tastatura
#include <stdio.h>
#include <stdlib.h>

///graful, vectorul cu noduri marcate folosite in BFS, vectorul de parinti folosit
///pentru generarea celui mai scurt drum, numarul de noduri, numarul de muchii
int** graph;
int* marked;
int* parent;
unsigned int nodes, edges;
///ne spune daca a fost sau nu gasit drum intre nodurile alese
int foundPath;

///structuri pentru coada folosita la BFS
typedef struct node{
    int value;
    struct node* next;
}Node;

typedef struct list{
    Node* first;
    Node* last;
}List;

///coada pentru BFS
List queue;

///citim graful din fisier
void ReadGraph();
///functie ajutatoare pentru afisat matricea de adiacenta
void PrintMatrix();
///adauga in coada
void Add(int value);
///sterge din coada
void Delete();
///verifica daca este vida coada
int Empty();
///parcurgerea in largime si generarea drumului
void BFS(int startNode, int endNode);
///returneaza primul element din coada
int GetFirst();
///printeaza drumul cel mai scurt folosinduse de vectorul de tati
void PrintPath(int currentNode);

int main()
{
    ReadGraph();
    ///PrintMatrix();
    int s, v;

    printf("graful are %u noduri si %u muchii, de la care doriti sa aflati drumul?",nodes,edges);
    printf("\ns: ");
    scanf("%d", &s);
    printf("v: ");
    scanf("%d", &v);
    BFS(s,v);
    if(foundPath){
        printf("drumul cel mai scurt de la nodul %d la nodul %d este\n",s,v);
        PrintPath(v);
    }
    else
        printf("nu exista drum intre aceste noduri");
    return 0;
}

void ReadGraph(){
    FILE* input = fopen("GRAF.TXT","r");
    fscanf(input,"%u %u", &nodes, &edges);

    ///aloca memorie pentru graf
    graph = malloc(sizeof(int)*(nodes+1));
    marked = calloc(sizeof(int),nodes+1);
    unsigned int i, j;

    for(i = 0; i <= nodes; i++){
        graph[i] = calloc(sizeof(int),(nodes+1));
    }

    int a, b;

    for(i = 0; i < edges; i++){
        fscanf(input,"%d %d", &a, &b);
        graph[a][b] = 1;
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
void BFS(int startNode, int endNode){
    parent = calloc(sizeof(int),nodes+1);
    ///adaugam nodul de start in coada
    Add(startNode);
    int i;
    int currentNode;
    ///nodul de start este deja marcat in coada
    marked[startNode]=1;
    ///ne oprim cand nu mai avem ce vizita sau am ajuns la destinatie
    while(!Empty() && currentNode!=endNode){
        ///nodul curent devine primul nod din coada
        currentNode = GetFirst();
        ///iteram prin vecinii nodului curent
        for(i = 1; i <=nodes; i++){
            ///daca avem muchie si nodul nu a mai fost introdus in coada
            ///atunci il introducem, il marcam si setam nodul curent sa fie parintele
            if(graph[currentNode][i] == 1 && marked[i] == 0){
                Add(i);
                marked[i]=1;
                parent[i]=currentNode;
            }
        }
        ///stergem primul element din coada
        Delete();
    }
    ///verificam daca am gasit drum
    if(currentNode == endNode)
        foundPath = 1;
}

///returneaza primul element din coada
int GetFirst(){
    if(queue.first != NULL)
        return queue.first->value;
    else return -1;
}

///afiseaza drumul folosindu-se de vectorul de tati
void PrintPath(int currentNode){
    if(currentNode){
        PrintPath(parent[currentNode]);
        printf("%d ", currentNode);
    }
}
