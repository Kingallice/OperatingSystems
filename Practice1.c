#include <stdio.h>
#include <stdlib.h>

#define ADD 50

void printHello();
void printNumber(int);
int loopNumber(int, int);

int main() {
    printNumber(193823);
    printHello();
    int ret = loopNumber(7, 11);
    printNumber(8);
    printf("\nRet Pointer: %p\n", &ret);
    return ret;
}

void printHello() {
    printf("Yo, Bro!\n");
}

void printNumber(int num){
    printf("Number: %d\n", num);
}

int loopNumber(int start, int end){
    int i;
    int acc = 0;
    for(i = start; i < end; i++){
        acc += i;
    }
    return acc * ADD;
}