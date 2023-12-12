#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

sem_t *semaphore;

void* worker(pid_t pid)
{
	sem_wait(semaphore);
	printf("Process %d - Entered\n", pid);
	
	for (int i = 0; i < 5; i++) {
		printf("Process %d - Holding (%d sec)\n", pid, i);
		sleep(1);
	}

	printf("Process %d - Exiting\n", pid);
	sem_post(semaphore);
}

int main(int argc, char *argv[]) {

	if (argc > 1) { sem_unlink("/example_sem2"); }

	semaphore = sem_open("/example_sem2", O_CREAT, 0777, 1);
	if (semaphore == SEM_FAILED) {
		perror("sem_open");
		exit(1);
	}
	
	/*
	if (fork() == 0) {
		// child 1
		worker(getpid());
		exit(0);
	} else if (fork() == 0) {
		// child 2
		worker(getpid());
		exit(0);
	} else {
		// parent
		// worker(getpid());
	}

	wait(NULL);
	wait(NULL);
	*/

	worker(getpid());

	return 0;
}

