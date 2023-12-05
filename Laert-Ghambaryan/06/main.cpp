#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <limits>
#include <thread>
#include <chrono>

struct ThreadData {
    const std::vector<uint32_t>* arr;
    int start;
    int end;
    uint32_t result;
};

void* calculateXORSum(void* threadDataPtr) {
    ThreadData* data = static_cast<ThreadData*>(threadDataPtr);
    uint32_t xorSum = 0;

    for (int i = data->start; i < data->end; ++i) {
        xorSum ^= (*data->arr)[i];
    }

    data->result = xorSum;
    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <NUM_THREADS>" << std::endl;
        return 1;
    }

    int numThreads = std::atoi(argv[1]);

    const int N = 100000;
    
    std::vector<uint32_t> randomNumbers;
    std::srand(static_cast<unsigned>(std::time(0)));
    for (int i = 0; i < N; ++i) {
        randomNumbers.push_back(std::rand() % std::numeric_limits<uint32_t>::max());
    }

    int chunkSize = N / numThreads;

    std::vector<std::pair<int, int>> chunks;
    for (int i = 0; i < numThreads - 1; ++i) {
        chunks.emplace_back(i * chunkSize, (i + 1) * chunkSize);
    }
    chunks.emplace_back((numThreads - 1) * chunkSize, N);

    std::vector<pthread_t> threads(numThreads);
    std::vector<ThreadData> threadData(numThreads);

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        threadData[i] = {&randomNumbers, chunks[i].first, chunks[i].second, 0};
        pthread_create(&threads[i], nullptr, calculateXORSum, &threadData[i]);
        pthread_detach(threads[i]);  
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    uint32_t finalXORSum = 0;
    for (const auto& data : threadData) {
        finalXORSum ^= data.result;
    }

    std::cout << "Total XOR sum: " << finalXORSum << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}

