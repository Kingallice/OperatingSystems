#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h> 

#define BUFFER_SIZE 64
#define QUEUE_SIZE 4

struct Semaphore{
    int value;
};

void customSignal(struct Semaphore);
void customWait(struct Semaphore);
void producer();
void consumer();
char * intToString(int);
char * concat(char*, char*);
char * substring(char*, int, int);
int indexOf(char*, char);
int strLen(char*);
int customRandom(int, int);
int parseInt(char*);

char buffer[BUFFER_SIZE];
struct Semaphore s1;

int main(){
    printf("Welcome to the Driver Simulation!\n*********************************\n\n");

    //Initialize Buffer
    int i;
    for(i = 0; i < sizeof(buffer); i++){
        buffer[i] = '\0';
    }
    
    //Initialize Semaphore    
    s1.value = 1;

    //Create Produce and Consumer
    pthread_t producerId, consumerId;
    pthread_create(&producerId, NULL, producer, NULL);
    pthread_create(&consumerId, NULL, consumer, NULL);
    
    pthread_join(producerId, NULL);
    pthread_join(consumerId, NULL);

    return 1;
}

void customSignal(struct Semaphore s){
    s.value++;
}

void customWait(struct Semaphore s){
    while(s.value <= 0);
    s.value--;
}


void producer(){
    while(1){
        //Lock Semaphore
        customWait(s1);
        //Gets time
        int t = time(NULL);
        
        //Generates entry
        char * timestr = intToString(t);
        char * randtemp = intToString(customRandom(60, 100));
        char * addspace = concat(" ", randtemp);
        char * tempstr = concat(timestr, addspace);
        char * entry = concat(tempstr, "\n");
        
        //Searches for end of buffer
        int i, end;
        for(i = 0; i < BUFFER_SIZE; i++){
            if(buffer[i] == '\0'){
                end = i;
                i = BUFFER_SIZE;
            }
        }
        
        //Gets len of entry and determines if entry can be added to buffer
        //If entry can be added, then adds to the end
        int len = strLen(entry);
        int remaining = BUFFER_SIZE-end;
        if(len < remaining){
            for(i = 0; i < len; i++){
                buffer[end+i] = entry[i];
            }
        }
        
        //Free temp strings
        free(timestr);
        free(randtemp);
        free(addspace);
        free(tempstr);
        free(entry);
        
        //Release Semaphore
        customSignal(s1);
    }
}

void consumer(){
    while(1){
        //Lock Semaphore
        customWait(s1);
        
        //Search buffer for entry
        int end = indexOf(buffer, '\n');
        char * found = substring(buffer, 0, end);
        
        //Search entry for temp strings
        int space = indexOf(found, ' ');
        char * timestr = substring(found, 0, space);
        char * tempstr = substring(found, space+1, indexOf(found, '\0'));
        
        //Parse integers out of temp strings
        int time = parseInt(timestr);
        int temp = parseInt(tempstr);
        
        printf("\nConsumed:\n\tBuffer[0] = %s\n\tTime Added: %d\n\tTemp Recorded: %d\n", found, time, temp);
        
        //Removes buffer[0] and moves the rest of the entries down
        int i = 0;
        int j = end+1;
        while(buffer[j] != '\0'){
            buffer[i] = buffer[j];
            i++;
            j++;
        }
        while(buffer[i] != '\0'){
            buffer[i] = '\0';
            i++;
        }
        
        //free temp strings        
        free(found);
        free(timestr);
        free(tempstr);

        //Release Semaphore
        customSignal(s1);
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

char * substring(char * str, int start, int len){
    if(len < 0){
        len = strLen(str) - start;
    }
        
    char * output = malloc(len * sizeof(char));
    output[len] = '\0';

    int i;
    for(i = 0; i < len; i++){
        output[i] = str[start+i];
    }
    return output;
}

int indexOf(char * str, char c){
    int len = strLen(str);
    int i;
    for(i = 0; str[i] != c && i < len; i++);
    if(i >= len)
        i = -1;
    return i;
}

int strLen(char * str){
    int idx = 0;
    while(str[idx] != '\0')
        idx++;
    return idx;
}

int customRandom(int lower, int upper){
    int diff = upper-lower;
    int random = rand();
    int out = random % diff;
    return lower + out;
}

int parseInt(char * str) {
    int i = 0, output = 0, multiplier = 1;
    while(str[i] >= '0' && str[i] <= '9'){
        output += (str[i] - '0') * multiplier;
        multiplier *= 10;
        i++;
    }
    return output;
}
