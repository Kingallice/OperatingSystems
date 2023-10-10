#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

#define WELCOME "\nWelcome to the Assignment 1! This program will add users to our database!\n"
#define START "\n\n****** PROGRAM START ******\n"
#define PRINT "\n\n****** BEGIN PRINTOUT ******\n"
#define FREE "\n\n****** BEGIN FREE ******\n"

#define USER_COUNT_PROMPT "\nPlease enter a number of users you would like to add: "
#define INVALID_PROMPT "Please enter an integer no larger than %d! Try again: "

#define NEW_USER_PROMPT "\n****** New User %d ******\n\n"
#define USER_NUMBER_PROMPT "\tEnter User Number: "
#define USERNAME_PROMPT "\tEnter Username: "
#define FIRST_NAME_PROMPT "\tEnter First Name: "
#define LAST_NAME_PROMPT "\tEnter Last Name: "

#define PRINT_USER_FORMAT "\n****** User Number %d Summary ******\n\n\tUser Number: %d\n\tUsername: %s\n\tUser First: %s\n\tUser Last: %s\n"

struct user
{
    int userNum;
    char * userName;
    char * userFirst;
    char * userLast;
};


void printWelcome();
int getNumUsers();
int clearStdin();
int addUsers(int, struct user[SIZE]);
char * addString(char *);
int addInt(int *, char *);
int printUsers(struct user[SIZE]);
void freeMemory(struct user[SIZE]);

int main(){
    printWelcome();
    
    int numUsers = getNumUsers();

    struct user users[SIZE];

    addUsers(numUsers, users);

    printUsers(users);

    freeMemory(users);

    return 0;
}

void printWelcome(){
    printf(WELCOME);
    printf(START);
}

int getNumUsers(){
    int num;
    char term;

    printf(USER_COUNT_PROMPT);

    for(;;) {
        if(scanf("%d%c",&num,&term) != 2 || term != '\n' || num > SIZE){
            printf(INVALID_PROMPT, SIZE);
            clearStdin();
        }
        else break;
    }
    return num;
}

int clearStdin(){
    int c = 0;
    while (('\n' != (c=fgetc(stdin))) && (c != EOF)) {
        if (c == EOF) break;
    }
    return 0;
}

int addUsers(int loopNum, struct user users[SIZE]){
    int i;
    for(i = 0; i < loopNum; i++){
        printf(NEW_USER_PROMPT, i+1);

        addInt(&users[i].userNum, USER_NUMBER_PROMPT);
        users[i].userName = addString(USERNAME_PROMPT);
        users[i].userFirst = addString(FIRST_NAME_PROMPT);
        users[i].userLast = addString(LAST_NAME_PROMPT);
    }
    users[i].userNum = 0;
}

char * addString(char * prompt){
    char * inputString = malloc(SIZE * sizeof(char));
    inputString[SIZE] = '\0';

    printf("%s", prompt);
    scanf("%s", inputString);
    return inputString;
}

int addInt(int * num, char * prompt){
    printf("%s", prompt);
    scanf("%d", num);
    return 0;
}

int printUsers(struct user users[SIZE]){
    printf(PRINT);

    int num = -1;
    int count = 0;

    while(users[count].userNum != 0 && count < SIZE){
        printf(PRINT_USER_FORMAT, count+1, users[count].userNum, users[count].userName, users[count].userFirst, users[count].userLast);
        count++;
    }
    return 0;
}

void freeMemory(struct user users[SIZE]){
    printf(FREE);

    int idx = 0;
    int count = 0;
    while(users[idx].userNum != 0 && count < SIZE){
        free(users[idx].userName);
        free(users[idx].userFirst);
        free(users[idx].userLast);

        idx++;
        count++;
    }
}