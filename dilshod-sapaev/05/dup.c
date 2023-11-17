#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main() {
	
	// open file
        int fd = open("out1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

	dup2(fd, 1);

	char **arguments = (char **)malloc(1 * sizeof(char *));
	arguments[0] = (char *)malloc(3 * sizeof(char));
	strcpy(arguments[0], "ls\0");
	int err = execvp("ls", arguments);
	if (err == -1) {
		printf("Error while executing `ls`\n");
	}
	
	// printf("out1.txt fd = %d\n", fd);
	// printf("Hello world\n");

	return 0;
}
