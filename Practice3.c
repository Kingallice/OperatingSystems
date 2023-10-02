#include <stdio.h>
#include <stdlib.h>

#define SIZE 200
#define print printf

void parse(char *, char *);
char * copyString(char *);
char * copySubstring(char *, int, int);

int main(int argc, char * argv[]){
    int i = 0;
    char * test = malloc(5);
    while(1 == 1){
        printf("%c", test[i]);
        i++;
    }
    if(argc != 3){
        printf("Wrong Input: Please enter {delimiter} {string}");
        return 0;
    }
    parse(argv[1], argv[2]);
}

void parse(char * delim, char * toParse){
    printf("The delimiter is: %s\nThe string to parse is: %s\n", delim, toParse);
    char * getBack = copyString(toParse);
    printf("Copied string: %s\n", getBack);

    int lower = 0;
    int upper = 0;
    int i = 0;
    while(toParse[i] != '\0'){
        if(toParse[i] == ':'){
            upper = i;
            printf("Lower: %d -- Upper: %d\nSubstring: %s\n\n", lower, upper, copySubstring(toParse, lower, upper));
            lower = i+1;
        }
        i++;
    }

//    char * partial = copySubstring(toParse, 5, 10);
//    print("Substring: %s\n", partial);
}

char * copyString(char * copyFrom){
    char * copyTo;
    copyTo = malloc(SIZE * sizeof(char));
    copyTo[SIZE] = '\0';

    int i = 0;
    while(copyFrom[i] != '\0'){
        copyTo[i] = copyFrom[i];
        i++;
    }
    copyTo[i] = '\0';
    return copyTo;
}

char * copySubstring(char * copyFrom, int start, int end){
    char * copyTo;
    copyTo = malloc(SIZE * sizeof(char));
    copyTo[SIZE] = '\0';

    int i;
    for(i = start; i < end; i++){
        copyTo[i-start] = copyFrom[i];

    }
    return copyTo;
}