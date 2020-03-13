///problema 3.6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TO_INT(x) x-'a'
#define true 1
#define false 0

///variabile globale
///
///
/// 'z' - 'a' = cate litere sunt in alfabet
/// folosim macro-ul TO_INT(x) pentru a accesa elementele graphului folosind litere
///
unsigned int graph['z'-'a']['z'-'a'];
///
/// un vector de frecventa in care notam nodurile parcurse
unsigned int visited['z'-'a'];
///
/// un vector de frecventa care contine nodurile pe care sa le parcurgem
unsigned int toVisit['z'-'a'];
///
/// nod pentru lista necesara in topological sort
struct Node{
    char value;
    struct Node* next;
};
///
/// stack pointer pentru a memora ultima pozitie in stiva
struct Node* sp = NULL;
///
/// bool ca in c++
typedef char bool;
///
///prototipuri de functii
///
/// adauga un element in stiva
void AddInStack(char value);
///
/// elimina ultimul element din stiva
void DeleteFromStack();
///
/// printeaza stiva
void PrintStack(struct Node* iter);
///
/// adauga o pereche de (x,y) cu proprietatea din enunt
void AddPair(char x, char y);
///
/// parcurgere depth first search
void DFS(char x);
///
/// adevarat daca au fost vizitate toate nodurile si fals in caz contrar
bool Empty();
///
/// sortarea topologica
void TopoSort();

int main()
{
    AddPair('a','b');
    AddPair('a','f');
    AddPair('b','h');
    AddPair('d','c');
    AddPair('d','e');
    AddPair('d','i');
    AddPair('e','i');
    AddPair('g','a');
    AddPair('g','b');
    AddPair('g','c');
    AddPair('i','c');
    AddPair('j','e');
    TopoSort();
    PrintStack(sp);
    return 0;
}

void AddInStack(char value){
    struct Node* n = (struct Node*)malloc(sizeof(struct Node*));
    n->value = value;
    if(sp == NULL){
        n->next = NULL;
        sp = n;
    }
    else{
        n->next = sp;
        sp = n;
    }
}

void DeleteFromStack(){
    struct Node* temp = sp;
    sp = sp->next;
    free(temp);
}

void PrintStack(struct Node* iter){
    if(iter != NULL)
    {
        printf("%c ", iter->value);
        PrintStack(iter->next);
    }
}

void AddPair(char x, char y){
    graph[TO_INT(x)][TO_INT(y)] = 1;
    toVisit[TO_INT(x)]=1;
    toVisit[TO_INT(y)]=1;
}

void DFS(char x){

    ///daca x a fost vizitat permanent nu mai continuam
    if(visited[TO_INT(x)]==2) return;

    ///daca x a fsot vizitat temporar atunci avem graf ciclic
    if(visited[TO_INT(x)]==1) {
        fprintf(stderr,"graful este ciclic, STOP");
        exit(-1);
    }
    ///marcam temporar nodul x
    visited[TO_INT(x)]=1;

    ///vizitam toti copii nodului x
    int i;
    for(i = 0; i < 'z'-'a'; i++){
        if(graph[TO_INT(x)][i] == 1)
                DFS('a'+i);
    }
    ///marcam permanent nodul x
    visited[TO_INT(x)]=2;

    ///adaugam nodul x in stiva
    AddInStack(x);
}

bool Empty(){
    int i;
    for(i = 0; i < 'z'-'a';i++)
        if(toVisit[i]!=0)
            if(visited[i]==0)
                return false;

    return true;
}
void TopoSort(){
    int i;
    while(!Empty()){
        for(i=0; i < 'z'-'a';i++){
            if(toVisit[i]==1 && visited[i]==0)
                DFS('a'+i);
        }
    }
}
