#include <iostream>
#include <random>
#include <pthread.h>
#include <chrono>

struct ThreadData {
    int* numbers;
    int size;
    int result;
};

void* calculateXOR(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    int partialResult = 0;

    for (int i = 0; i < data->size; ++i) {
        partialResult ^= data->numbers[i];
    }

    data->result = partialResult;

    pthread_exit(nullptr);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_threads>\n";
        return 1;
    }

    int numberOfThreads = std::stoi(argv[1]);
    const int N = 100000000;

    // Generating random numbers in a larger range (1 to 100000)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-100000000, 100000000);

    int* numbers = new int[N];
    for (int i = 0; i < N; ++i) {
        numbers[i] = dis(gen);
    }

    // Creating threads
    pthread_t threads[numberOfThreads];
    ThreadData threadData[numberOfThreads];

    int numbersPerThread = N / numberOfThreads;
    int remainder = N % numberOfThreads;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0, startIdx = 0; i < numberOfThreads; ++i) {
        threadData[i].numbers = numbers + startIdx;
        threadData[i].size = numbersPerThread + (i < remainder ? 1 : 0);

        pthread_create(&threads[i], nullptr, calculateXOR, &threadData[i]);

        startIdx += threadData[i].size;
    }

    // Waiting for threads to finish
    for (int i = 0; i < numberOfThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Total result
    int totalResult = 0;
    for (int i = 0; i < numberOfThreads; ++i) {
        totalResult ^= threadData[i].result;
    }

    // Freeing memory
    delete[] numbers;

    std::cout << "Total XOR result: " << totalResult << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds\n";

    return 0;
}

