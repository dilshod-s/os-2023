#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

#define N 100000001

int* random_array; // Array of random numbers
int thread_count; // Number of threads
uint64_t* local_results; // Array for local results

// Function executed by each thread
void* worker(void* data) {
    int thread_index = *((int*)data); // Thread index
    int block_size = N / thread_count; // Calculate block size for each thread
    int start = thread_index * block_size; // Block start
    int end = (thread_index == thread_count - 1) ? N : (thread_index + 1) * block_size; // Block end

    uint64_t local_result = 0; // Store local bitwise sum

    for (int i = start; i < end; ++i) { // Calculate bitwise XOR sum for its block of data
        local_result ^= random_array[i];
    }

    local_results[thread_index] = local_result; // Save result in the local_results array at the thread_index
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Two arguments expected: file name and thread count.\n");
        return 1;
    }

    thread_count = atoi(argv[1]); // Initialize the number of threads

    if (thread_count <= 0) {
        printf("Thread count must be a positive number.\n");
        return 1;
    }

    random_array = (int*)malloc(N * sizeof(int)); // Initialize array of random numbers
    if (random_array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        random_array[i] = rand(); // Generate random integers
    }

    local_results = (uint64_t*)malloc(thread_count * sizeof(uint64_t)); // Array for local results with size equal to the number of threads
    if (local_results == NULL) {
        printf("Memory allocation failed.\n");
        free(random_array);
        return 1;
    }

    pthread_t threads[thread_count]; // Array to store thread IDs
    int thread_indices[thread_count]; // Array for thread indices

    struct timeval start, end; // Variables to store start and end time
    gettimeofday(&start, NULL); // Get the current time as the start time

    for (int i = 0; i < thread_count; ++i) { // Create and launch threads, passing each thread its index
        thread_indices[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_indices[i]);
    }

    for (int i = 0; i < thread_count; ++i) { // Join threads
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL); // Get the current time as the end time

    uint64_t result = 0;
    for (int i = 0; i < thread_count; ++i) { // Calculate XOR of local results (overall bitwise sum)
        result ^= local_results[i];
    }

    printf("Bitwise sum: %llu\n", result);
    printf("Execution time: %ld microseconds\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));

    // Free allocated memory
    free(random_array);
    free(local_results);

    return 0;
}