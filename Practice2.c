#include <stdio.h>
#include <stdlib.h>

#define SIZE 20
#define NAME "Enter Name: "

struct Student
{
    int stuNum;
    char * fName;
    char * lName;
};

struct Rectangle
{
    float width;
    float length;
};

char * getInput(char *);
int printWelcome(char *);
int addStudents(int, struct Student *);
int printStudents(struct Student *);

int main(){
    char * name = getInput(NAME);
    printWelcome(name);
    // struct Student s1;
    // s1.stuNum = 93726727;
    // s1.fName = "Noah";
    // s1.lName = "Mosel";

    struct Student class[20];
    int result;
    result = addStudents(3, class);
    printStudents(class);

    struct Rectangle r1;
    r1.length = 23.4;
    r1.width = 2.63;


    return 0;
}

char * getInput(char * prompt){
    printf("%s",prompt);

    char * input;
    input = malloc(SIZE * sizeof(char));

    scanf("%s", input);
    input[SIZE] = '\0';

    return input;
}

int printWelcome(char * name){
    printf("Hello there, %s!\n\n", name);

    return 0;
}

int addStudents(int num, struct Student class[20]){

    int i;
    for(i = 0; i < num; i++){
        class[i].stuNum = i;
        class[i].fName = getInput(NAME);
        class[i].lName = getInput(NAME);
    }
    return 0;
}

int printStudents(struct Student * class){
    int i;
    for(i = 0; i < 20; i++){
        if(class[i] == NULL)
            break;
        printf("Student Number: %d\nStudent First: %s\nStudent Last: %s\n", class[i].stuNum, class[i].fName, class[i].lName);
    }
    return 0;
}