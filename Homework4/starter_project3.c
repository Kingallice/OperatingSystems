#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
 
char ** parse(char delim, char * word);
void pointerPrint(char ** argv);
char * checkString(char ** parsedInput, char ** path, char * input);
void exec(char * pathToFile, char ** parsedInput);
void exec2(char * pathToFile1, char * pathToFile2, char ** parsedInput1, char ** parsedInput2);

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
}

char ** parse(char delim, char * word) {

}

void pointerPrint(char ** path){

}

char * checkString(char ** parsedInput, char ** path, char * input){

}

void exec(char * pathToFile, char ** parsedInput){

}

void exec2(){
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
}
