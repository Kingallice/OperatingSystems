#include <stdio.h>
#include <stdlib.h>

int getUserInput();

int main(){
    int limit = getUserInput();

    int i;
    for(i = 0; i < limit; i++){
        printf("%d\n", i);
    }

    return 0;
}

int getUserInput(){
    int input;
    printf("Please define a limit: ");

    scanf("%d", &input);
    return input;
}