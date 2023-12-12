#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

	int pipefd[2];
	pipe(pipefd);

	int pid1 = fork();
	if (pid1 < 0) {
		exit(1);
	}

	if (pid1 == 0) {
		// child1, writes to pipe
		close(pipefd[0]);
		dup2(1, pipefd[1]);
		exec("ls", "-l")
	}
	
	int pid2 = fork();
        if (pid2 < 0) {
                exit(1);
        }

	if (pid2 == 0) {
		// child2, reads from pipe
		close(pipefd[1]);
		printf("I am child 2\n");
		
		char buf[20];
		read(pipefd[0], buf, 20);
		printf("%s", buf);

		exit(0);
	}

	wait(NULL);
	wait(NULL);
	return 0;
}
