#include <stdio.h>
#include <stdlib.h>

int getUserInput();
float calcAvg(int);
void farewell();

int main() {
    printf("\nWelcome to Lab 2!\n\n");
    int choice;
    choice = getUserInput();
    printf("\nYou chose the value: %d\n", choice);
    float mean;
    mean = calcAvg(choice);
    printf("The mean is: %f\n", mean);
    farewell();
    return 0;
}

int getUserInput(){
    printf("Please enter a number from 1 to 10: ");
    int num;
    scanf("%d", &num);
    return num;
}

float calcAvg(int num){
    int i;
    float total = 0;
    for(i = 0; i < num; i++){
        total += i;
    }
    return total/num;
}

void farewell(){
    printf("\nFarewell! Thank you for using this program!\n\n");
}