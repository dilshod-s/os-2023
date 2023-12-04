#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

#define N 100000001

int* arr; //массив случайных чисел
int numThreads; //количество потоков
uint64_t* localResult; //массив локальных результатов

//функция, которую выполняет каждый поток
void* worker(void* data) {
    int threadIndex = *((int*)data); //индекс потока
    int blockSize = N / numThreads; //размер блока для каждого потока вычисляет
    int start = threadIndex * blockSize; //начало блока
    int end; //конец блока
    if (threadIndex == numThreads - 1) {
        end = N;
    } else {
        end = (threadIndex + 1) * blockSize;
    }

    uint64_t localRes = 0; //хранится локальная побитовая сумма

    for (int i = start; i < end; i++) { //вычисляем побитовую сумму для своего блока данных
        localRes ^= arr[i];
    }

    localResult[threadIndex] = localRes; //сохраняем результат в массиве localResults по индексу threadIndex
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <количество_потоков>\n", argv[0]);
        return 1;
    }

    numThreads = atoi(argv[1]); //инициализируем количество потоков (atoi - из строки в целое число)

    if (numThreads <= 0) {
        printf("Количество потоков должно быть положительным числом\n");
        return 1;
    }

    arr = (int*)malloc(N * sizeof(int)); //инициализируем массив случайных чисел
    for (int i = 0; i < N; ++i) {
        arr[i] = rand();
    }

    localResult = (uint64_t*)malloc(numThreads * sizeof(uint64_t)); //массив для локальных результатов размером в количество потоков

    //запускаем потоки
    pthread_t threads[numThreads]; //тут находятся ID потоков
    int threadInd[numThreads]; //тут индексы потоков(от 0 до (numThreads - 1))

    struct timeval start, end; //создаем структуру, в которой будет храниться время. start и end для того,
    // чтобы показать начало и конец выполнения программы
    gettimeofday(&start, NULL); //записываем текущее время в start. Это нужно для замера времени выполнения программы.
    // NULL для использования системного времени

    for (int i = 0; i < numThreads; ++i) { //создаем и запускаем потоки, передавая каждому индекс потока
        //индексы нужны для определения, какой блок данных будет обработан каждым потоком
        threadInd[i] = i;
        pthread_create(&threads[i], NULL, worker, &threadInd[i]); //создаем поток
    }

    for (int i = 0; i < numThreads; ++i) { //завершаем потоки
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL); //текущее время сохраняем в end

    uint64_t result = 0;
    for (int i = 0; i < numThreads; ++i) { //вычисляем xor из локальных результатов(общую побитовую сумму)
        result ^= localResult[i];
    }


    printf("Побитовая сумма: %llu\n", result);
    printf("Затраченное время: %ld мкс\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    // (end.tv_sec - start.tv_sec) это разница в секундах между временем завершения и временем начала
    //умножаем на 1000000, чтоб преобразовать секунды в миллисекунды
    //(end.tv_usec - start.tv_usec) тут бы добавляем разницу в микросекундах между временем завершения и временем начала
    //думаем, что будет тип long

    //овобождаем память
    free(arr);
    free(localResult);

    return 0;
}