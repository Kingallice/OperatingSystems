#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BUFFER_SIZE 64

char buffer[BUFFER_SIZE];

void producer();
void consumer();
char * intToString(int);
char * concat(char*, char*);
int strLen(char*);
int random(int lower, int upper);

int main(){
    printf("Welcome to the Driver Simulation!\n*********************************\n\n");

    producer();

    return 1;
}

void producer(){
    while(1){
        
        int t = time(NULL);
        char * entry = intToString(t);
        
        printf("%s\n", concat(entry, concat(" ", intToString(random(60, 100)))));
        // int i;
        // for(i = 0; i < sizeof(buffer); i++){
        //     printf
        // }
        // printf("%c", '\60'+);
    }
}

void consumer(){
    while(1){
        int idx = 0;
    }
}

char * intToString(int num){
    char * output = malloc(20 * sizeof(char));
    output[20] = '\0';

    int idx = 0;
    while(num > 0){
        output[idx] = 48+(num % 10);
        num = num/10;
        idx++;
    }
    output[idx] = '\0';

    return output;
}

char * concat(char * str1, char * str2){
    int len1 = strLen(str1);
    int len2 = strLen(str2);

    char * output = malloc((len1 + len2) * sizeof(char));
    output[len1 + len2] = '\0';

    int idx = 0;
    while(str1[idx] != '\0'){
        output[idx] = str1[idx];
        idx++;
    }
    while(str2[idx-len1] != '\0'){
        output[idx] = str2[idx-len1];
        idx++;
    }

    return output;
}

int strLen(char * str){
    int idx = 0;
    while(str[idx] != '\0')
        idx++;
    return idx;
}

int random(int lower, int upper){
    int diff = upper-lower;
    int random = rand();
    int out = random % diff;
    printf("\nRandom\n\tLower: %d\n\tUpper: %d\n\tDifference: %d\n\tRandom: %d\n\tRandom mod Difference: %d\n\tOutput: %d\n", lower, upper, diff, random, out, lower+out);
    return lower + out;
}