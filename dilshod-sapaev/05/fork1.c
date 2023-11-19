#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[], char *envp[]) {
	/*
	int i = 0;
	while (envp[i] != NULL) {
		printf("%d: %s\n", i, envp[i]);
		i++;
	}
	*/

	char *errcode = (char *) malloc(256);

	
	pid_t pid;
	if ((pid = fork()) == 0 ) {
		printf("I am Child\n");
		char **arguments = (char **)malloc(1 * sizeof(char *));
		arguments[0] = (char *)malloc(3 * sizeof(char));
		strcpy(argv[0], "ls\0");
		int err = execvp("ls", argv);
		if (err == -1) {
			printf("Error while executing `ls`\n");
			perror(errcode);
		}
	} else {
		// sleep(0);
		int status = 0;
		wait(&status);
		printf(
			"I am Parent. Child exited with status %d\n",
			status
		);
	}
}
