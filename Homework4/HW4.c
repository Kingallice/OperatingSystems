#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
 
char * getVariable(char **, char *);
int getLength(char *);
int getSize(char **);
char * strcopy(char *);
char * substring(char *, int, int);
char ** parse(char delim, char * word);
void pointerPrint(char ** argv);
char * checkString(char ** parsedInput, char ** path, char * input);
void exec(char * pathToFile, char ** parsedInput);
void exec2(char * pathToFile1, char * pathToFile2, char ** parsedInput1, char ** parsedInput2);
void freeArray(char **);

int main(int argc, char ** argv, char ** envp){
	/* 1.
	     - Use this file as an outline; however, I recommend starting with the file
		that you turned in for part 2 of the project.
	     - We will only be adding one function (and any additional functions you
		think would be useful) and a few lines to the main method.	
	*/
	/* 2.
	     - We first need to check if there is a pipe in the input. This means, you
		need to check if the character '|' is in the input variable. 
		- If it is, you will need to call the exec2 function
			- Before you call the exec2 function, you need to split the input
			   into 2 parts. The parts before and after the '|' character.
			- You will do this by calling the parse function.
				- Then, you will need to get the path to the file and the
				   parsed input for each of these 2 strings.
				   HINT: This will be done exactly the same as when you get
					the parameters that you pass into the exec function,
					you will just have to do it twice, one fore each string.
				- For example: if the input was 'ls -h -a -l|grep test'
					you would parse this into two strings 'ls -h -a -l' and
					'grep test'.
					- You would then have to parse each of these with a delimiter 
					   of ' ' to get each piece of the command and then find the
					   path to the file for 'ls' and the path to the file for 'grep'
		- If it is not, you will call the exec function (the same as in part 2)
		NOTE: This must be done inside of the loop, as you are supposed to be able to enter
			as many commands as you would like.
	*/
    
    //Get PATH variable
    char * path = getVariable(envp, "PATH");
    
    //Parse PATH
    char ** PATHS = parse(':',path);

    //Print Point info of PATH
	pointerPrint(PATHS);
	
	//Malloc Input
	char * input = malloc(200);
	
	//Read and execute inputs
	while(1){
	    //Print and Ready for inputs
    	printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\nSUPER BASH $");
     	scanf("%[^\n]%*c", input); // reads input until a new line symbol, then the newline is discarded
     	
     	if(strcmp(input,"exit") == 0)
     	    break;
    
        //Check for '|' and parse if found
        char ** pipedInputs = parse('|', input);
        if(getSize(pipedInputs)==2){
            //Parse input
            char ** parsedInput1 = parse(' ', pipedInputs[0]);
            char ** parsedInput2 = parse(' ', pipedInputs[1]);
            
            //Look for program
        	char * file1 = checkString(parsedInput1, PATHS, pipedInputs[0]);
        	char * file2 = checkString(parsedInput2, PATHS, pipedInputs[1]);
        	
        	//Print Pointer info of input
        	pointerPrint(parsedInput1);
        	pointerPrint(parsedInput2);
        
            //Execute
            exec2(file1, file2, parsedInput1, parsedInput2);
        }
        else {
            //Parse input
            char ** parsedInput = parse(' ', input);
            
            //Look for program
        	char * file = checkString(parsedInput, PATHS, input);
        	
        	//Print Pointer info of input
        	pointerPrint(parsedInput);
        
            //Execute
            exec(file, parsedInput);
        }
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

int getSize(char ** arrIn){
    int idx = 0;
    while(arrIn[idx] != NULL){
        idx++;
    }
    return idx;
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

char ** parse(char delim, char * strIn) {
	char ** array = malloc(30 * sizeof(char *));
    array[30] = NULL;

    int start = 0, idx = 0, count = 0;
    while(strIn[idx] != '\0'){
        if(strIn[idx] == delim){
			char * temp = substring(strIn, start, idx-start);
// 			if(getLength(temp) == 0)
// 			    continue;
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
	printf("Address 0x%p\n", (void *)&path);
	int idx = 0;
	while(path[idx] != NULL){
		printf("Base[%d] Address 0x%p Pointer Value 0x%p String=%s\n",idx, &path[idx], (void *)path[idx], path[idx]);
		idx++;
	}
}

char * checkString(char ** parsedInput, char ** path, char * input){
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
	printf("String = '%s'\nNumber of pointers = %d\n", input, pointerCount);
	return command;
}

void exec(char * pathToFile, char ** parsedInput){
    int state;
    if(fork() == 0){
        execv(pathToFile, parsedInput);
    }
    else {
        wait(&state);
    }
}

void exec2(char * pathToFile1, char * pathToFile2, char ** parsedInput1, char ** parsedInput2){
	/* 3.
	     - Here, you will need to call execv, fork, wait, dup2, amd close
		- You can begin by copying the code that you have for the exec function.
	*/
	
	/* 4.
	     - If you are in the child process, you will need to create a pipe and use the output of
		the first command as input to the second command.
		- I included an example of using a pipe under Files->Project Part 3 in Canvas which
		   should be very helpful.
	*/
	int thePipe[2];
	
	pipe(thePipe);
	
	pid_t p1 = fork();
	int state1, state2;
	
	if(p1 == 0) // Process 1
	{
		close(thePipe[0]); //Close read end of pipe
		dup2(thePipe[1], STDOUT_FILENO);
		close(thePipe[1]);

        state1 = execv(pathToFile1, parsedInput1);
        exit(1);
	}
	else //Parent Process
	{
		close(thePipe[1]);
		
	    pid_t p2 = fork();
        if(p2 == 0){ //Process 2
		    dup2(thePipe[0], STDIN_FILENO);
		    close(thePipe[0]);
		
            state2 = execv(pathToFile2, parsedInput2);
            exit(1);
        }
        close(thePipe[0]);
        wait(&state1);
        wait(&state2);
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