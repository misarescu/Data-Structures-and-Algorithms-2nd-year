#include <stdio.h>
#include <stdlib.h>

///stiva in care construim combinatiile
int* stack[150];
int table[10][10];
int size = 3;

void InitStack();
///functia de backtrack
void BackTrack(int level);
///functia de validare a solitiei
int Valid(int position);
///functia care returneaza daca am gasit o solutie
int Solution(int level);
///functia de printat
void Print();

int main()
{
    InitStack();
    BackTrack(1);
    return 0;
}

void InitStack(){
    int i;
    int j;
    int k = 1;
    for(i = 1; i <= size; i++)
        for(j = 1; j <= size; j++){
            stack[k] = &table[i][j];
            k++;
        }
}

void BackTrack(int level){
    if(level < size*size+1){
        if(Solution(level))
            Print();
        else{
            int i;
            for(i = 1; i >= 0; i--){
                *stack[level]=i;
                if(Valid(level))
                {
                    BackTrack(level+1);
                }
            }
        }
    }
}

int Valid(int position){
    int i = (position-1)/size + 1;
    int j = position - ((i-1)*size);
    ///todo: fa conditiile ca daca se ataca acei calutei
    /// sa ii faci mielusei(fa functia ma)
    return 1;
}

int Solution(int level){
    int horseNumber = 0;
    int i;
    int j;
    for(i = 1; i <= size; i++)
        for(j = 1; j <= size; j++)
            horseNumber += table[i][j];
    return horseNumber == size;
}

void Print(){
    int i;
    int j;
    printf("\n");
    for(i = 1; i <= size; i++)
    {
        for(j = 1; j <= size; j++)
            printf("%d\t", table[i][j]);
        printf("\n");
    }
}
