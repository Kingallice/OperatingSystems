#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 20

char * getUserInput(char *, char *);
void printWelcome(char *);
void printUserInput(char *, char *, char *);

int main(){
    char * welcomePrompt = "Welcome to C Lab3!";
    char * firstNamePrompt = "Please enter your first name: ";
    char * lastNamePrompt = "Please enter your last name: ";
    char * outputFormat = "\n%s %s, welcome to CYBR 401!\n\n";
    char * inputFormat = "%19s";

    printWelcome(welcomePrompt);
    
    char * firstName = getUserInput(firstNamePrompt, inputFormat);
    char * lastName = getUserInput(lastNamePrompt, inputFormat);

    printUserInput(firstName, lastName, outputFormat);

    free(firstName);
    free(lastName);

    return 0;
}

char * getUserInput(char * prompt, char * format){
    char * userInput;
    userInput = malloc(STR_SIZE * sizeof(char));
    userInput[STR_SIZE] = '\0';

    printf("%s", prompt);

    scanf(format, userInput);

    return userInput;
}

void printWelcome(char * welcome){
    printf("\n%s\n\n", welcome);
}

void printUserInput(char * fName, char * lName, char * format){
    printf(format, fName, lName);
}