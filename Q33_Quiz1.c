#include <stdio.h>
#include <stdlib.h>

#define SIZE 25
#define PROMPT "Enter First Name: "

char * getUserString(char *);
void printUserString(char *);

int main(){
    char * userString = getUserString(PROMPT);
    printUserString(userString);
    return 0;
}

char * getUserString(char * prompt){
    printf("%s", prompt);
    char * input = malloc(SIZE * sizeof(char));
    input[SIZE] = '\0';
    scanf("%s", input);
    return input;
}

void printUserString(char * inputString){
    printf("%s", inputString);
}
