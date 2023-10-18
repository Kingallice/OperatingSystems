#include <stdio.h>
#include <stdlib.h>

void countNum(int);

int main(){
    countNum(10);
    return 0;
}

void countNum(int max){
    int i;
    for(i = 0; i < max; i++){
        printf("%d\n", i);
    }
}