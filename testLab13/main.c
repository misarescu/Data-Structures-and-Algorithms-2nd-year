//subiectul 16
//sa se implementeze operatorul de inmultire pentr unumerele mari
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//folosim greedy pentru ca obtinem reuzltatul inmultirii primului numar
//cu fiecare cifra in parte a celui de al doilea nr si le adunam in rezultatul final
int* a;
int* b;

int result[100];
int sizeResult;

int* MultiplyRow(int x[], int y, int *sizeX, int shift);
int* Multiply(int x[], int y[], int sizeX, int sizeY);
int* Add(int x[], int y[], int sizeX, int sizeY);
int* Convert(const char* number, int* numSize);
void PrintNum(int x[], int sizeX);

int main()
{
    char nr[255];
    printf("a: ");
    fflush(stdin);
    scanf("%s", nr);
    int sizeA;
    a = Convert(nr, &sizeA);
    PrintNum(a,sizeA);

    printf("\nb: ");
    fflush(stdin);
    scanf("%s", nr);
    int sizeB;
    b = Convert(nr, &sizeB);
    PrintNum(b,sizeB);

    Multiply(a,b,sizeA,sizeB);
    printf("\n");
    PrintNum(result,sizeResult);
    return 0;
}

int* Add(int x[], int y[], int sizeX, int sizeY)
{
    int i;
    int remainder = 0;
    int sum = 0;
    for(i = 0; i < sizeX && i < sizeY; i++){
        sum = x[i]+y[i] + remainder;
        remainder = 0;
        while(sum >= 10){
            remainder++;
            sum-=10;
        }
        result[i] = sum;
    }
    if(i >= sizeX)
    {
        sizeResult = sizeY;
        for(i; i < sizeY; i++)
        {
            sum = y[i]+remainder;
            remainder = 0;
            while(sum >= 10){
                remainder++;
                sum-=10;
            }
            result[i] = sum;
        }
    }
    else if(i >= sizeY)
    {
        sizeResult = sizeX;
        for(i; i < sizeX; i++)
        {
            sum = x[i]+remainder;
            remainder = 0;
            while(sum >= 10){
                remainder++;
                sum-=10;
            }
            result[i] = sum;
        }
    }
    if(remainder)
        result[i]=remainder,sizeResult++;
    return 0;
}

int* Convert(const char* number, int* numSize){
    //cu i mergem pe stringul numarului
    //cu j populam vectorul
    int i;
    int j = 0;
    *numSize = strlen(number);
    int* result = malloc(sizeof(int)*(*numSize));

    for(i = 0; i < (*numSize); i++)
        result[i] = (int)(number[(*numSize)-i-1]-'0');

    return result;
}

void PrintNum(int x[], int sizeX){
    int i;
    for(i = sizeX-1; i >= 0; i--)
        printf("%d ", x[i]);
}

int* MultiplyRow(int x[], int y, int *sizeX, int shift)
{
    int i;
    int prod = 1;
    int remainder=0;
    for(i = 0; i < (*sizeX); i++){
        prod = x[i]*y+remainder;
        remainder = 0;
        if(prod >= 10){
            remainder = prod/10;
            prod%=10;
        }
        x[i]=prod;
        prod = 1;
    }
    if(remainder){
        x[i]=remainder;
        (*sizeX)++;
    }
    //il inmultim pe i cu 10^shift
    /*
    for(i = sizeX+shift - 1; i >= shift; i--){
        x[i] = x[i-shift];
    }
    for(i = shift-1; i >= 0; i--)
        x[i] = 0;
    (*sizeX)+= shift;*/
    return 0;
}

int* Multiply(int x[], int y[], int sizeX, int sizeY)
{
    //r de la row
    int r[50];

    int sizeR;

    int i;
    int j;

    //luam un vector de 0-uri la fel de mare ca si x
    //x este numarul de referinta iar y este numarul din care luam cf sa le inmultim cu x
    sizeResult = sizeX;

    for(i = 0; i < sizeY; i++)
    {
        //il copiem pe x in r
        //si il 'inmultim' cu 10^i
        sizeR = sizeX;
        for(j = i; j < sizeX+i; j++){
            r[j] = x[j];
        }

        MultiplyRow(r,y[i],&sizeR,i);
        Add(result,r,sizeResult, sizeR);
    }
    return 0;
}
