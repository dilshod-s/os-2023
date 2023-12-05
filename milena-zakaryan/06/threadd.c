#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>

const unsigned long long N = 100000000;

// Structure for passing arguments to the stream
typedef struct {
    size_t start;
    size_t end;
    uint64_t partial_sum;
} ThreadArgs;

uint64_t total_sum = 0; // Total amount

// Function for generating random numbers and calculating the bit sum in a given range
void* calculateXOR(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    uint64_t partial_sum = 0;

    // Generating random numbers and calculating the bitwise sum in a given range
    for (size_t i = thread_args->start; i < thread_args->end; ++i) {
        uint64_t random_number = rand();
        partial_sum ^= random_number;
    }

    thread_args->partial_sum = partial_sum;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }

    size_t num_threads = atoi(argv[1]);

    // Initialize an array with arguments for each thread
    ThreadArgs thread_args[num_threads];
    pthread_t threads[num_threads];

    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Divide work between threads
    size_t chunk_size = N / num_threads;
    for (size_t i = 0; i < num_threads; ++i) {
        thread_args[i].start = i * chunk_size;
        thread_args[i].end = (i + 1) * chunk_size;
        thread_args[i].partial_sum = 0;
        pthread_create(&threads[i], NULL, calculateXOR, &thread_args[i]);
    }

    // Measure execution time
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Wait for all threads to complete
    for (size_t i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
        total_sum ^= thread_args[i].partial_sum;
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Total XOR: %llu\n", total_sum);
    printf("Execution time: %.6f seconds\n", execution_time);

    return 0;
}