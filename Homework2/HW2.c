#include <stdlib.h>
#include <stdio.h>

int getLength(char *);
char * substring(char *, int, int);
char ** split(char *, char);
void splitInput(char *, char);
void freeArray(char **);

int main(int argCount, char ** argsArray){
    if(argCount != 3){
        printf("\nError: Please pass a delimiter and string to be parsed!\n");
    }
    else if(getLength(argsArray[1]) != 1){
        printf("\nError: The delimiter is the first argument passed and should only be one character long!\n");
    }
    else {
        splitInput(argsArray[2],argsArray[1][0]);
    }

    return 0;
}

int getLength(char * strIn){
    int idx = 0;
    while(strIn[idx] != '\0'){
        idx++;
    }
    return idx;
}

char * substring(char * strIn, int start, int length){
    char * sub = malloc(30 * sizeof(char));
    sub[30] = '\0';

    int idx = 0;
    while(strIn[start+idx] != '\0' && idx < length){
        sub[idx] = strIn[start+idx];
        idx++;
    }
    sub[idx] = '\0';
    return sub;
}

char ** split(char * strIn, char delimiter){
    char ** array = malloc(30 * sizeof(char *));
    array[30] = NULL;

    int start = 0, idx = 0, count = 0;
    while(strIn[idx] != '\0'){
        if(strIn[idx] == delimiter){
            array[count] = substring(strIn, start, idx-start);

            count++;
            start = idx+1;
        }
        idx++;
    }
    array[count] = substring(strIn, start, idx-start);
    return array;
}

void splitInput(char * strIn, char delimiter){
    char ** splitText = split(strIn, delimiter);

    int idx = 0;
    while(splitText[idx] != NULL){
        printf("%s Length %d\n", splitText[idx], getLength(splitText[idx]));

        idx++;
    }

    freeArray(splitText);
}

void freeArray(char ** array){
    int idx = 0;
    while(array[idx] != NULL){
        free(array[idx]);

        idx++;
    }
    free(array);
}