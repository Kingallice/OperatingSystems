#include <stdio.h>
#include <stdlib.h>

#define SIZE 20
#define NAME "Noah Mosel"

struct account {
    char * name;
    int amount;
};

void printStruct(struct account);

int main(){
    struct account a1;
    a1.name = NAME;
    a1.amount = SIZE;

    printStruct(a1);

    return 0;
}

void printStruct(struct account inAcc){
    printf("Name: %s\nAmount: %d", inAcc.name, inAcc.amount);
}