/*
    3.
    fisierul PRINTER.TXT
    model,culoare,tip,pret,producator
    minim 30 inregistrari
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50


typedef struct element{
    int model;
    char color[10];
    char type[255];
    float price;
    char producer[255];
    int empty;
}Element;

Element hashTable[MAX_SIZE];

void InitTable();
void Read();
int HashFuntion(int key);
int QuadraticHash(int position, int j);
void Add(int id, char* color, char* type, float price, char* producer);
void Delete(int key);
void PrintTable();
void PrintElement(int key);

int main(){
    InitTable();
    Read();
    //PrintTable();
    ///meniu
    char cmd;
    int run = 1;
    int key;
    while(run){
        printf("apasa f pentru a gasi un nod, d pentru a sterge un nod, p pentru a printa tabela, altceva pentru a iesi\n");
        scanf("%c",&cmd);
        switch(cmd){
        case 'f':
            printf("care este id-ul pe care doriti sa-l cautati?\n_:");
            fflush(stdin);
            scanf("%d", &key);
            fflush(stdin);
            PrintElement(key);
            break;
        case 'd':
            //char key[255];
            printf("care este id-ul pe care doriti sa-l stergeti?\n_:");
            fflush(stdin);
            scanf("%d", &key);
            fflush(stdin);
            Delete(key);
            break;
        case 'p':
            fflush(stdin);
            PrintTable();
            break;
        default:
            run = 0;
        }
    }
    return 0;
}

void Read(){
    FILE* input = fopen("PRINTER.TXT","r");
    if(input != NULL)
    {
        while(!feof(input)){
            char line[255];
            fgets(line,255,input);
            char* result;
            int model;
            char color[10];
            char type[255];
            float price;
            char producer[255];
            result = strtok(line,",");
            model = atoi(result);
            result = strtok(NULL,",");
            strcpy(color,result);
            result = strtok(NULL,",");
            strcpy(type,result);
            result = strtok(NULL,",");
            price = atof(result);
            result=strtok(NULL,"\n");
            strcpy(producer,result);
            Add(model,color,type,price,producer);
        }
    }
    fclose(input);
}

void Add(int model, char* color, char* type, float price, char* producer){
    int position = HashFuntion(model);
    if(hashTable[position].empty == 1){
        hashTable[position].empty = 0;
        hashTable[position].model=model;
        strcpy(hashTable[position].color,color);
        strcpy(hashTable[position].type,type);
        hashTable[position].price = price;
        strcpy(hashTable[position].producer,producer);
    }
    else{
        int j = 1;
        do{
            //printf("nodul %d a avut o coliziune la locatia %d\n", model, position);
            position = QuadraticHash(position,j);
            j++;
        }while(hashTable[position].empty == 0);

        hashTable[position].empty = 0;
        hashTable[position].model=model;
        strcpy(hashTable[position].color,color);
        strcpy(hashTable[position].type,type);
        hashTable[position].price = price;
        strcpy(hashTable[position].producer,producer);;
    }
}
void Delete(int key){
    int position = HashFuntion(key);
    if(hashTable[position].model == key)
        hashTable[position].empty = 1;
    else{
        int j = 0;
        do{
            position = QuadraticHash(position,j);
            j++;
        }while(!(hashTable[position].model == key) && j < MAX_SIZE);
        if(j == MAX_SIZE){
            printf("niciun nod cu acest id\n");
            return;
        }
        hashTable[position].empty = 1;
    }
}

void InitTable(){
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        hashTable[i].empty = 1;
    }
}

int HashFuntion(int key){
    int sum = 0;
    int i;
    while(key){
        sum+=(key%10);
        key/=10;
    }
    return sum % MAX_SIZE;
    //return key % MAX_SIZE;
}

int QuadraticHash(int position, int j){
    return (position + j * j) % MAX_SIZE;
}

void PrintTable(){
    int i;
    for(i = 0; i < MAX_SIZE; i++){
        if(hashTable[i].empty == 0)
            printf("[%d]:\t%d, %s, %s, %.2f, %s\n",i,hashTable[i].model,hashTable[i].color,hashTable[i].type,hashTable[i].price,hashTable[i].producer);
        else
            printf("[%d]:\tLiber\n", i);
    }
}

void PrintElement(int key){
    int position = HashFuntion(key);
    if(hashTable[position].model == key)
    {
        if(hashTable[position].empty == 0)
            printf("%d, %s, %s, %.2f, %s\n",hashTable[position].model,hashTable[position].color,hashTable[position].type,hashTable[position].price,hashTable[position].producer);
        else
            printf("niciun nod cu acest id\n");
    }
    else{
        int j = 0;
        do{
            position = QuadraticHash(position,j);
            j++;
        }while(!(hashTable[position].model == key) && j < MAX_SIZE);
        if(j == MAX_SIZE){
            printf("niciun nod cu acest id\n");
            return;
        }
        if(hashTable[position].empty == 0)
            printf("%d, %s, %s, %.2f, %s\n",hashTable[position].model,hashTable[position].color,hashTable[position].type,hashTable[position].price,hashTable[position].producer);
        else
            printf("niciun nod cu acest id\n");
    }
}
