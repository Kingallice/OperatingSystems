#include <stdlib.h>
#include <stdio.h>

char * substring(char *, int, int);
int equal(char *, char *);
char ** parse(char *, char);
void printArray(char **);
void freeArray(char **);

int main(int argc, char * argv[], char ** envp) {
    int i;
    char ** arrStr;
    for(i = 0; envp[i] != NULL; i++) {
        char * found = substring(envp[i], 0, 4);
        if(equal("Path", found)){
            //printf("%s\n\n", envp[i]);
            arrStr = parse(envp[i], ';');
        }
        free(found);
    }
    printArray(arrStr);

    freeArray(arrStr);

    return 0;
}

char * substring(char * strIn, int start, int end){
    char * strOut = malloc((end-start) * sizeof(char));
    strOut[end-start] = '\0';
    //printf("%s, %d, %d\n",strIn, start, end);

    int i;
    for(i = start; i < end; i++){
        strOut[i-start] = strIn[i];
    }
    //printf("********* OUT ********\n%s\n", strOut);
    return strOut;
}

int equal(char * in1, char * in2){
    int i;
    int good = 1;
    for (i = 0; in1[i] != '\0' && in2[i] != '\0'; i++)
    {
        if(in1[i] != in2[i]){
            good = 0;
            break;
        }
    }
    return good;
}

char ** parse(char * strIn, char delimiter){
    char ** chunks = malloc(200 * sizeof(char *));
    chunks[200] = NULL;

    int start = 5, end = 5, count = 0;
    //substring(strIn, 179, 222);
    while(strIn[end] != '\0'){
        //printf("%c-", strIn[end+10]);
        if(strIn[end] != delimiter){
            end++;
            //printf("%d\n", end);
        }
        else {
            //printf("*******************%d\n", end);
            char * temp = substring(strIn, start, end);
            //printf("\n%d,%d,%d -> %s\n", start, end, count, temp);
            chunks[count] = temp;


            count++;
            start = end+1;
            end++;
        }
        
    }
    // printf("%c__",strIn[end]);
    return chunks;
}

void printArray(char ** array){
    int idx = 0;
    while(array[idx] != NULL){
        printf("%s\n", array[idx]);
        idx++;
    }
}

void freeArray(char ** array){
    int idx = 0;
    while(array[idx] != NULL){
        free(array[idx]);
        idx++;
    }
}