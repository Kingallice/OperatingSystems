#include <stdio.h>
#include <stdlib.h>

#define WELCOME "\nWelcome to the Process Manager\n"
#define END "\nEnding Process Manager\n\n"
#define SIZE 10

void printWelcome();
struct process makeProcess();
int getID();
char * getName();
void printProcess(struct process);
void printEnd();
void freeProc(struct process);

struct process
{
    int id;
    char * name;
};

int main(){
    printWelcome();

    struct process p1;
    p1 = makeProcess();

    printProcess(p1);

    freeProc(p1);
    printEnd();
    return 0;
}

void printWelcome(){
    printf("%s", WELCOME);
}

struct process makeProcess(){
    printf("\n****** GET INPUT ******\n\n");

    struct process p1;
    p1.id = getID();
    p1.name = getName();

    return p1;
}

int getID(){
    printf("Enter ID: ");
    int num;
    scanf("%d", &num);

    return num;
}

char * getName(){
    printf("Enter Name: ");

    char * temp = malloc(SIZE * sizeof(char));
    temp[SIZE] = '\0';

    scanf("%s", temp);

    return temp;
}

void printProcess(struct process p1){
    printf("\n****** PRINT OUT ******\n\n");
    
    printf("Process ID: %d\n", p1.id);
    printf("Process Name: %s\n", p1.name);
}

void printEnd(){
    printf("%s", END);
}

void freeProc(struct process p1){
    free(p1.name);
}