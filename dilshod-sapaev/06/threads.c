#include<stdio.h>
#include<pthread.h>

int A[2];

void *worker(void *data) {
	int index = ((int *) data)[0];
	printf("I am worker %d\n", index);
	for (int i = 0; i < 100000000; i++) {
		A[index] += 1;
	}
	
	pthread_exit(NULL);
}

int main() {
	pthread_t tid1;
	pthread_t tid2;
	int data1 = 0;
	int data2 = 1;
	
	pthread_create(&tid1, NULL, worker, &data1);
	pthread_create(&tid2, NULL, worker, &data2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("A:[%d, %d]\n", A[0], A[1]);

	return 0;
}
