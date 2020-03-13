#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Film{
    char titlu[100];
    int an;
    int durata;
    char gen[100];
    char studio[100];
    char producator[100];
    struct Film* next;
};

struct Film* first = NULL;

void Add();
void Print();

int main()
{
    Add();
    Print();
    return 0;
}
void Print(){
    struct Film* temp = first;
    printf("\n");
    while(temp != NULL){
        printf("\n\ntitlu:%s\nan:%d\ndurata:%d\ngen:%s\nstudio:%s\nproducator:%s\n",temp->titlu,temp->an,temp->durata,temp->gen,temp->studio,temp->producator);
        temp = temp->next;
    }
}

void Add(){
    FILE* input = fopen("FILM.TXT","r");
    if(input != NULL){
        while(!feof(input)){
            struct Film* temp = (struct Film*)malloc(sizeof(struct Film));
            fscanf(input,"%s,",temp->titlu);
            temp->titlu[strlen(temp->titlu)-1]='\0';
            fscanf(input,"%d,",&temp->an);
            fscanf(input,"%d,", &temp->durata);
            fscanf(input,"%s,",temp->gen);
            temp->gen[strlen(temp->gen)-1]='\0';
            fscanf(input,"%s,",temp->studio);
            temp->studio[strlen(temp->studio)-1]='\0';
            fscanf(input,"%s\n",temp->producator);
            temp->next = NULL;
            if(first == NULL){
                first = temp;
            }
            else{
                if(strcmp(temp->studio,first->studio)>0){
                    temp->next = first;
                    first = temp;
                }

                else if(strcmp(temp->studio,first->studio)==0){
                    if(temp->durata > first->durata){
                        temp->next = first;
                        first = temp;
                    }
                }//endif
                else{
                    struct Film* p = first;
                    char run = 1;
                    while(p->next != NULL && run){
                        if(strcmp(temp->studio,p->studio)>0){
                            temp->next = p->next;
                            p->next = temp;
                            run = 0;
                        }
                        else if(strcmp(temp->studio,p->studio)==0){
                            if(temp->durata > p->durata){
                                temp->next = p->next;
                                p->next = temp;
                                run = 0;
                            }
                        }
                        p=p->next;
                    }
                    if(!p->next)
                        p->next = temp;
                }
            }//endwhile
        }
    }
}
