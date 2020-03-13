#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

typedef char bool;

struct Locomotiva{
    int id;
    char tip[50];
    float greutate;
};

struct Locomotiva depou[100];

bool running = true;
int tail;
int head;

void PrintMenu();
void Input();
void Init();
void Add();
void Print();
void Delete();
void AddFromFile(FILE* readingFile);
void WriteToFile(FILE* wriringFile);

int main()
{
    Init();
    //varf = -1;
    while(running){
        system("cls");
        PrintMenu();
        Input();
    }

    FILE* dataFile;
    dataFile = fopen("Depou.txt", "w");

    WriteToFile(dataFile);

    fclose(dataFile);

    return 0;
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
    case 'q':
        running = false;
        break;
    }
}

void Init(){
    tail = -1;
    head = 0;
    FILE* dataFile;
    dataFile = fopen("Depou.txt", "r");

    if(dataFile){
        int n;
        fscanf(dataFile,"%d", &n);
        int i;
        for(i = 0; i < n; i++)
            AddFromFile(dataFile);
    }

    fclose(dataFile);
}

void Add(){
    tail++;
    printf("id: ");
    scanf("%d", &depou[tail].id);
    printf("tip: ");
    scanf("%s",&depou[tail].tip);
    printf("greutate: ");
    scanf("%f",&depou[tail].greutate);
}

void Delete(){
    if(head < tail)
        head++;
}

void Print(){
    int i;

    for(i =head; i <= tail; i++){
        printf("id: %d \ntip: %s \ngreutate: %f\n\n",depou[i].id, depou[i].tip, depou[i].greutate);
    }
}

void PrintMenu(){
    printf("Press a to add\nPress d to delete\nPress p to print\nPress q to quit\n");
}

void AddFromFile(FILE* readingFile){
    tail++;
    fscanf(readingFile,"%d", &depou[tail].id);
    fscanf(readingFile,"%s",&depou[tail].tip);
    fscanf(readingFile,"%f",&depou[tail].greutate);
}

void WriteToFile(FILE* writingFile){
    int i;
    fprintf(writingFile,"%d\n", tail-head+1);
    for(i = head; i <= tail; i++)
        fprintf(writingFile,"%d\n%s\n%f\n",depou[i].id, depou[i].tip, depou[i].greutate);
}
