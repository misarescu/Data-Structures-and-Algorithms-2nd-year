/**
3. Se presupune ca in fisierul text RPTINTER.TXT exista, cate o inregistrare pe linie, sub forma
model, culoare, tip, pret, producator
Se presupune ca model este un numar si este unic. culoare poate lua valorile {'D','N'}
pretul este in euro. Se cere folosidn o structura de date de tip arbore binar de cautare
sa se citeasca datele din fisier si sa se afiseze un meniu care sa permita cautarea unei imprimante
dupa model. Fisierul cu date de intrare va fi completata cu minim 30 de inregistrari.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct printer{
    int model;
    char color;
    char type[100];
    float price;
    char manufacturer[100];
}Printer;

typedef struct tNode{
    Printer value;
    struct tNode* right;
    struct tNode* left;
}TNode;

TNode* treeRoot = NULL;
FILE* input;

void CreateTree();
TNode* GetNode(const int model);
TNode* ReadNode();
int Add(const TNode* m);
void PrintNode(TNode* node);

int main()
{
    char run = 1;
    char command;
    int model;
    input = fopen("PRINTER.TXT", "r");
    CreateTree();
    while(run){
        fprintf(stdout,"c: cautare\nq: iesire\n");
        fscanf(stdin,"%c", &command);
        switch(command){
        case 'c':
            fprintf(stdout,"ce model? ");
            fscanf(stdin,"%d", &model);
            PrintNode(GetNode(model));
            break;
        case 'q':
            run = 0;
            break;
        }
    }
    fclose(input);
    return 0;
}

///creem arborele de cautare
void CreateTree(){
    ///citim cate noduri sunt
    int n;
    fscanf(input,"%d\n", &n);

    TNode* currentNode;
    ///introducem nodurile in arbore
    int i;
    for(i = 0; i < n; i++){
        TNode* nodeRead = ReadNode();
        Add(nodeRead);
    }
}

///functie ajutatoare pentru adaugare
int Add(const TNode* m){
    if(treeRoot == NULL){
        treeRoot = m;
        return 1;
    }
    else{
        char go = 1;
        TNode* currentNode = treeRoot;
        while(go){
            ///strcmp(a,b)
            /// > 0 => a > b
            /// < 0 => a < b
            if(currentNode->value.model < m->value.model){
                if(currentNode->right == NULL)
                {
                    go = 0;
                    currentNode->right = m;
                }
                else
                    currentNode = currentNode->right;
            }
            else if(currentNode->value.model > m->value.model){
                if(currentNode->left == NULL)
                {
                    go = 0;
                    currentNode->left = m;
                }
                else
                    currentNode = currentNode->left;
            }
            else {
                free(m);
                return -1;
            }
        }

    }
    return 1;
}

///citim un nod din fisier
TNode* ReadNode(){
    TNode* temp = malloc(sizeof(TNode));
    fscanf(input,"%d,%c,%s,%f,%s\n", &temp->value.model,&temp->value.color,temp->value.type,&temp->value.price,temp->value.manufacturer);
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

///obtinem un nod dupa model
TNode* GetNode(const int model){
    if(treeRoot == NULL){
        return NULL;
    }
    else{
        char go = 1;
        TNode* currentNode = treeRoot;
        while(go){
            ///daca am gasit modelul returnam nodul
            if(currentNode->value.model == model){
                return currentNode;
            }
            ///daca modelul este mai mare mergem pe stanga
            else if(currentNode->value.model < model){
                currentNode = currentNode->right;
            }
            ///daca nu mergem pe dreapta
            else if(currentNode->value.model > model){
                currentNode = currentNode->left;
            }
        }

    }
}
///functie ajutatoare ca sa afisam un nod
void PrintNode(TNode* node){
    fprintf(stdout,"\n%d,%c,%s,%f,%s\n",node->value.model,node->value.color,node->value.type,node->value.price,node->value.manufacturer);
}
