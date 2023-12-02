#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

char * buffer;

int main(){
    printf("Welcome to the Driver Simulation!\n*********************************\n\n");

    buffer = malloc(BUFFER_SIZE * sizeof(char));
    buffer[BUFFER_SIZE] = '\0';

    return 1;
}

void producer(){
    while(1){
        int idx = 0;
        while(buffer[idx] != '\0')
            idx++;
        if(idx < BUFFER_SIZE){
            
        }
    }
}

void consumer(){
    while(1){
        int idx = 0;
    }
}