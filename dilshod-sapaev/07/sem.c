#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* worker(void* data)
{
	pthread_t tid = ((pthread_t *) data)[0];
	sem_wait(&semaphore);
	printf("Thread %ld - Entered\n", tid);
	sleep(0);
	printf("Thread %ld - Exiting\n", tid);
	sem_post(&semaphore);
}

int main()
{
	sem_init(&semaphore, 0, 3);
	pthread_t t[3];

	pthread_create(&t[0], NULL, worker, &t[0]);
	pthread_create(&t[1], NULL, worker, &t[1]);
	pthread_create(&t[2], NULL, worker, &t[2]);
        pthread_join(t[0], NULL);
        pthread_join(t[1], NULL);
	pthread_join(t[2], NULL);

	sem_destroy(&semaphore);
	return 0;
}

