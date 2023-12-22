#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <cstdint>
#include <sys/time.h>

#define N 100000001

int* arr; // Array of random numbers
int countThreads; // Number of threads
uint64_t* localResult; // Array for local results

void* worker(void* data) {
    int threadIndex = *static_cast<int*>(data);
    int blockSize = N / countThreads;
    int start = threadIndex * blockSize;
    int end = (threadIndex == countThreads - 1) ? N : (threadIndex + 1) * blockSize;

    uint64_t localRes = 0;

    for (int i = start; i < end; i++) {
        localRes ^= arr[i];
    }

    localResult[threadIndex] = localRes;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <number of threads>" << std::endl;
        return 1;
    }

    countThreads = std::atoi(argv[1]);

    if (countThreads <= 0) {
        std::cout << "Number of threads should be a positive integer." << std::endl;
        return 1;
    }

    arr = new int[N];

    for (int i = 0; i < N; ++i) {
        arr[i] = std::rand();
    }

    localResult = new uint64_t[countThreads];

    pthread_t threads[countThreads];
    int threadInd[countThreads];

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < countThreads; ++i) {
        threadInd[i] = i;
        pthread_create(&threads[i], NULL, worker, &threadInd[i]);
    }

    for (int i = 0; i < countThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);

    uint64_t result = 0;
    for (int i = 0; i < countThreads; ++i) {
        result ^= localResult[i];
    }

    std::cout << "Bitwise XOR result: " << result << std::endl;
    std::cout << "Execution time: " << (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec) << " µs" << std::endl;

    delete[] arr;
    delete[] localResult;

    return 0;
}

