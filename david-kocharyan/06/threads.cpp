#include <iostream>
#include <pthread.h>
#include <chrono>
#include <random>
#include <mutex>

struct Range {
    size_t start;
    size_t end;
    pthread_mutex_t* mutex; 
};

const size_t N = 100'000'008;
size_t xorSum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void* task_06(void* data) {
    Range* range = static_cast<Range*>(data);
    size_t start = range->start;
    size_t end = range->end;
    pthread_mutex_t* threadMutex = range->mutex;
    unsigned long long int res = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long int> dis(-100'000'000, 100'000'000);

    for (size_t i = start; i < end; ++i) {
        const long long int o = dis(gen);
        res ^= o;
    }

    
    pthread_mutex_lock(threadMutex);
    
    xorSum ^= res; // Critical section
    
    pthread_mutex_unlock(threadMutex);

    delete range;
    return nullptr;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " `number of threads`" << std::endl;
        return 1;
    }

    size_t numofthreads = std::stoi(argv[1]);
    size_t chunkSize = N / numofthreads;
    pthread_t threads[numofthreads];

    auto startTime = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numofthreads; ++i) {
        Range* range = new Range{i * chunkSize, (i + 1) * chunkSize, &mutex}; 
        pthread_create(&threads[i], nullptr, task_06, range);
    }

    for (size_t i = 0; i < numofthreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Sum " << xorSum << std::endl;
    std::cout << "Time " << duration.count() << " millisec" << std::endl;

    return 0;
}

