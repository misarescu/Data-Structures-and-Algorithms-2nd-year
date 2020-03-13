///problema 3.5 din laboratorul 1
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef char bool;

bool running = true;

struct Locomotiva{
    int id;
    char tip[50];
    float greutate;
    struct Locomotiva* next;
};

struct List{
    struct Locomotiva* head;
    struct Locomotiva* tail;
};

struct List depou;

void PrintMenu();
void Input();
void Init();
void Add();
void Print();
void Delete();
void DeleteByVal(int ID);

int main()
{
    Init();
    while(running){
        system("cls");
        PrintMenu();
        Input();
        ///system("pause");
    }
    return 0;
}

void PrintMenu(){
    printf("Press a to add\nPress d to delete\nPress p to print\nPress q to quit\n");
}

void Input(){
    char cmd = getche();
    switch(cmd){
    case 'a':
        printf("\nyou pressed a\n");
        Add();
        system("pause");
        break;
    case 'd':
        Delete();
        break;
    case 'p':
        Print();
        system("pause");
        break;

    case 'r':
        printf("Remove by id: ");
        int val;
        scanf("%d",&val);
        DeleteByVal(val);
        break;
    case 'q':
        running = false;
        break;
    }
}

void Init(){
    depou.head = NULL;
    depou.tail = NULL;
}

void Add(){
    ///creem o noua locomotiva pentru a o introduce in lista
    struct Locomotiva* new_Locomotiva = malloc(sizeof(struct Locomotiva));
    printf("id: ");
    scanf("%d",&new_Locomotiva->id);
    printf("tip: ");
    scanf("%s",&new_Locomotiva->tip);
    printf("greutate: ");
    scanf("%f",&new_Locomotiva->greutate);
    new_Locomotiva->next=NULL;
    if(depou.head == NULL){
        depou.head = new_Locomotiva;
        depou.tail = new_Locomotiva;
    }
    else{
        depou.tail->next = new_Locomotiva;
        depou.tail = new_Locomotiva;
    }
}

void Print(){
    struct Locomotiva* plimbator = depou.head;
    printf("\n");
    while(plimbator != NULL){
        printf("id: %d \ntip: %s \ngreutate: %f\n\n",plimbator->id, plimbator->tip, plimbator->greutate);
        plimbator = plimbator->next;
    }
}

void Delete(){
    if(depou.head == NULL){
        printf("\nalready empty\n");
        system("pause");
    }
    else{
        if(depou.head->next != NULL){
            struct Locomotiva* old_Head = depou.head;
            depou.head = depou.head->next;
            free(old_Head);
            printf("\ndeleted\n");
            system("pause");
        }
        else{
            struct Locomotiva* old_Head = depou.head;
            depou.head = depou.head->next;
            free(old_Head);
            printf("\ndeleted\n");
            system("pause");
            depou.head = NULL;
        }
    }
}

void DeleteByVal(int ID){
    if(depou.head == NULL){
        exit(-1);
    }
    if(depou.head->id == ID){
        Delete();
    }
    else{
        struct Locomotiva* p = depou.head;
        while(p->next != NULL){
            if(p->next == ID){
                struct Locomotiva* temp = p->next;
                p->next = p->next->next;
                free(temp);
                return;
            }
            p = p->next;
        }
    }
}
