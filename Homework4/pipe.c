#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argcount, char ** arguments, char ** environment)
{
	int thePipe[2];
	pipe(thePipe);
	pid_t id = fork();
	if(id == 0) // child Process
	{
		char array[100]; 
		close(STDIN_FILENO);
		close(thePipe[1]);
		dup2(thePipe[0], STDIN_FILENO);
		scanf("%s", array);
		printf("The array is %s\n", array);
	}
	else //Parent Process
	{
		close(STDOUT_FILENO);
		close(thePipe[0]);
		dup2(thePipe[1], STDOUT_FILENO);
		printf("Hello");
	}
	
}
