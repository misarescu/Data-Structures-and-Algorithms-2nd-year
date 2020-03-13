#include <stdio.h>
#include <stdlib.h>

///Nod pentru arbore(tree node => TNode)
typedef struct tNode{
    int value;
    unsigned int numOfChilds;
    struct tNode** childs;
}TNode;

///Nod pentru coada(queue node => QNode)
typedef struct qNode{
    TNode* value;
    struct qNode* next;
}QNode;

///Nod pentru stiva(stack node => SNode)
typedef struct sNode{
    TNode* value;
    struct sNode* next;
}SNode;

TNode* treeRoot = NULL;
QNode* queueFirst = NULL;
QNode* queueLast = NULL;
SNode* stackPeak = NULL;

///Functii pentru arbore
TNode* CreateTree();
void Print();

///Functii pentru coada
void AddInQueue(TNode* value);
void DeleteFromQueue();

///Functii pentru stiva
void AddInStack(TNode* value);
void DeleteFromStack();

int main()
{
    treeRoot = CreateTree();
    Print();

    return 0;
}

void AddInQueue(TNode* value){
    if(value != NULL){
        QNode* temp = malloc(sizeof(QNode));
        temp->value = value;
        temp->next = NULL;
        if(queueLast == NULL){
            queueFirst = temp;
            queueLast = temp;
        }
        else{
            queueLast->next = temp;
            queueLast = temp;
        }
    }
}

void DeleteFromQueue(){
    if(queueFirst == NULL)
        return;
    else{
        QNode* oldFirst = queueFirst;
        queueFirst = queueFirst->next;
        free(oldFirst);
    }
}

void Print(){
    TNode* it = treeRoot;
    int i;
    AddInQueue(it);
    do{
        ///Parcurgere in BFS(Breadth First Search)
        it = queueFirst->value;
        fprintf(stdout,"%d ",queueFirst->value->value);
        for(i = 0; i < it->numOfChilds; i++){
            AddInQueue(it->childs[i]);
        }
        DeleteFromQueue();
    }while(queueFirst!=NULL);
}

TNode* CreateTree(){
    FILE* input = fopen("input.txt","r");
    if(input != NULL){
        unsigned int n;
        fscanf(input,"%u", &n);
        unsigned int i;
        while(n != 0){
            ///citire un nod si fii sai
            int val;
            fscanf(input,"%d", &val);
            unsigned int noc;
            fscanf(input,"%u", &noc);

            ///alocare nod
            TNode* node = malloc(sizeof(TNode));
            node->value = val;
            node->numOfChilds = noc;
            if(noc > 0)
                node->childs = malloc(sizeof(TNode)*noc);
            else
                node->childs = NULL;
            ///Eliminam din stiva nodurile care sunt copiii nodului curent
            ///Daca numOfChilds este mai mare ca 0(are copii)
            for(i = 0; i < node->numOfChilds; i++){
                ///punem node->numOfChilds - i -1 pentru a pune invers
                ///altfel copiii vin pusi invers
                ///nu ii gresit dar afiseaza altfel
                node->childs[node->numOfChilds-i-1] = stackPeak->value;
                DeleteFromStack();
            }
            ///Adaugam nodul in stiva
            AddInStack(node);


            n--;
        }
    }
    fclose(input);
    return stackPeak->value;
}

void AddInStack(TNode* value){
    if(value != NULL){
        SNode* temp = malloc(sizeof(SNode));
        temp->value = value;
        temp->next = NULL;
        if(stackPeak ==NULL)
            stackPeak = temp;
        else{
            temp->next = stackPeak;
            stackPeak = temp;
        }
    }
}
void DeleteFromStack(){
    if(stackPeak == NULL)
        return;
    else{
        SNode* temp = stackPeak;
        stackPeak = stackPeak->next;
        free(temp);
    }
}
