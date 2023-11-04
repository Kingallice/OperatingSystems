#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

char * getVariable(char **, char *);
int getLength(char *);
char * substring(char *, int, int);
char ** parse(char delim, char * word);
void pointerPrint(char ** argv);
char * checkString(char ** parsedInput, char ** path, char * input);
char * strcopy(char *);
void exec(char * pathToFile, char ** parsedInput);
void freeArray(char **);

int main(int argc, char ** argv, char ** envp){

	char * path = getVariable(envp, "PATH");
	
 /* 2.
	- Search through each element of envp to find the string that starts with 'PATH'
		- The environment variable that starts with 'PATH' is the path that is searched for binary executables
		- An example of printing each element of envp is shown in the envp_example.c file on Canvas
		- Do not hard code the index that begins with 'PATH'. You must search for it.
		- You will then need to use the parse function to parse the the string in envp that was found previously. (Hint: the delimiter will be ":")
			- Call pointerPrint on the result of the parse function.
 */
	char ** PATHS = parse(':',path);

	pointerPrint(PATHS);

	
	char * input = malloc(200);

    while(1){
            
     /* 4.
    	- Uncomment the following 3 lines
     */
    	printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
    	printf("SUPER BASH $");
     	scanf("%[^\n]%*c", input); // reads input until a new line symbol, then the newline is discarded
    
     /* 6.
    	- Call the checkString function to find the path to the file that you will need to execute
    	- Call the pointerPrint function on the parsedInput passed into the checkString function
     */
        char ** parsedInput = parse(' ', input);
        
    	char * file = checkString(parsedInput, PATHS, input);
    	pointerPrint(parsedInput);
    
     /* 8.
    	- Call the exec function 
     */
        exec(file, parsedInput); 
     /* 9.
    	- Put steps 4, 6, and 8 in a loop so you can enter as many commands as you want
     */
    }

}

char * getVariable(char ** envp, char * name){
	char * variable;
	int idx = 0;
	while(envp[idx] != NULL){
		char * temp = substring(envp[idx], 0, getLength(name));
		int compare = strcmp(temp , name);
		free(temp);
		if(compare == 0){
			break;
		}
		idx++;
	}
	variable = substring(envp[idx], getLength(name)+1, -1);
	return variable;
}

int getLength(char * strIn){
    int idx = 0;
    while(strIn[idx] != '\0'){
        idx++;
    }
    return idx;
}

char * substring(char * strIn, int start, int length){
    char * sub = malloc(200 * sizeof(char));
    sub[200] = '\0';

    int idx = 0;
	if(length == -1){
		while(strIn[start+idx] != '\0'){
			sub[idx] = strIn[start+idx];
			idx++;
		}
	}
	else {
		while(strIn[start+idx] != '\0' && idx < length){
			sub[idx] = strIn[start+idx];
			idx++;
		}
	}
    sub[idx] = '\0';
    return sub;
}

char ** parse(char delim, char * strIn){
 /* 1.
	- Copy and paste the parser you wrote from Project Part 1 here
	- You may have to make a few modifictions to make it work with this function
 */
	char ** array = malloc(30 * sizeof(char *));
    array[30] = NULL;

    int start = 0, idx = 0, count = 0;
    while(strIn[idx] != '\0'){
        if(strIn[idx] == delim){
			char * temp = substring(strIn, start, idx-start);
			array[count] = temp;

            count++;
			idx++;
            start = idx;
        }
		else {
	        idx++;
		}
    }
    if(start != idx){
        array[count] = substring(strIn, start, idx-start);
        count++;
    }
    array[count] = NULL;
    return array;
}

void pointerPrint(char ** path){
 /* 3.
	- Here we first want to print the address of the variable path
	- Next, for each string in the variable path, print the address of the string, the pointer value of the string, and the actual string.
	- See the screenshot in the assignment description to see how the result should look.
 */
	printf("Address 0x%p\n", (void *)&path);
	int idx = 0;
	while(path[idx] != NULL){
		printf("Base[%d] Address 0x%p Pointer Value 0x%p String=%s\n",idx, &path[idx], (void *)path[idx], path[idx]);
		idx++;
	}
}

char * checkString(char ** parsedInput, char ** path, char * input){
 /* 5.
	- Here, the variable parsedInput is the result of running the variable input through the parse function with a delimiter of ' '.
	- The variable path is the same that is passed in to the pointerPrint function
	- We want to search through each element in path to see if we can find the file to execute the command given in input.
		- To do this, we need to concatenate the current element in the variable path that we are looking at with a '/' and then with the first element in the variable input.
			- For example, with an input of 'ls -a' the current element in the variable path could be '/bin', then we will need to add '/' and then 'ls',
			  this gives a result of '/bin/ls'. We will use this later on to know exactly what file to execute.
	- After the file is found, you need to print the input and then print the number of pointers, which will be one more than the number of arguments.
		- For example, 'ls -a' would have 3 pointers. See the screenshot in the assignment description to see how the result should look.
	- Return the whole path to the file that you found previously, from this example it would be '/bin/ls'.
 */
	struct stat sb;

	char * command;
	int i;
	for(i = 0; path[i] != NULL; i++){
		if(path[i][getLength(path[i])-1] != '/')
			path[i] = strcat(path[i], "/");
		command = strcopy(path[i]);
		command = strcat(command,parsedInput[0]);
	    printf("Checking %s\n",command);
	    if(stat(command, &sb) == 0){
	        printf("FOUND!\n");
	        break;
	    }
	    free(command);
	}
	int pointerCount = 1;
	for(i = 0; parsedInput[i] != NULL; i++){
	    pointerCount++;
	}
	printf("String = %s\nNumber of pointers = %d\n", input, pointerCount);
	return command;
}

char * strcopy(char * str){
    char * strOut = malloc(200 * sizeof(char));
    strOut[200] = '\0';
    
    int i;
    for(i = 0; str[i] != '\0'; i++){
        strOut[i] = str[i];
    }
    return strOut;
}

void exec(char * pathToFile, char ** parsedInput){
 /* 7.
	- Need to call execv, fork, and wait here.
	- fork() returns the pid, which is an integer.
		- If the pid is 0, then you have the child process and will need to call execv
		- Otherwise, you have the parent process and you will need to call wait to wait for the child process to finish. 
 */
    int state;
    if(fork() == 0){
        execv(pathToFile, parsedInput);
    }
    else {
        wait(&state);
    }
}

void freeArray(char ** array){
	int idx = 0;
	while(array[idx] != NULL){
		free(array[idx]);
		idx++;
	}
	free(array);
}