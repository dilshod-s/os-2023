
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 10

void execute_command(char *command) {
	char *arguments[MAX_ARGUMENTS];
	int i = 0;

	
	char *token = strtok(command, " ");
	while (token != NULL && i < MAX_ARGUMENTS - 1) {
		arguments[i++] = token;
		token = strtok(NULL, " ");
	}
	arguments[i] = NULL; 

	pid_t pid = fork();

	if (pid == 0) 
	{
	    
		execvp(arguments[0], arguments);
		perror("execvp");
		exit(EXIT_FAILURE);
		
	} else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
	} else 
	{
	
		perror("fork");
	}
}

int main() {
	char command[MAX_COMMAND_LENGTH];

	while (1) 
	{
		printf("$ ");

		if (fgets(command, sizeof(command), stdin) == NULL) 
		{
			break; 
		}

		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0) 
		{
			break;
		}

		execute_command(command);
	}

	return 0;
}
