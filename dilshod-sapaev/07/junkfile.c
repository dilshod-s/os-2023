#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int fp = open("tmp.txt", O_CREAT | O_RDWR, 0777);
	fork();

	int res = write(fp, "Hello World\n", 12);
	printf("Written %d bytes to file\n", res);
}
