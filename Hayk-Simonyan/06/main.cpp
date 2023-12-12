#include <iostream>
#include <pthread.h>
#include <random>
#include <chrono>
#include <vector>

std::vector<int> dataSet;
std::vector<int> resultValues;

void* processData(void* arguments)
{
    unsigned int* range = static_cast<unsigned int*>(arguments);
    unsigned int index = range[0];
    unsigned int start = range[1];
    unsigned int end = range[2];
    unsigned long long int localSum = 0;

    for (unsigned int i = start; i < end; i++)
        localSum ^= dataSet[i];

    resultValues[index] = localSum;

    return nullptr;
}

void generateRandomData(int dataSize)
{
    std::random_device randomDevice;
    std::mt19937 numberGenerator(randomDevice());
    std::uniform_int_distribution<> distribution(-10000, 10000);

    for (int i = 0; i < dataSize; ++i)
        dataSet.push_back(distribution(numberGenerator));
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <DataSize> <ThreadsCount>" << "\n";
        return 1;
    }

    int dataSize = std::stoi(argv[1]), threadCount = std::stoi(argv[2]);

    generateRandomData(dataSize);

    pthread_t threadId;
    std::vector<pthread_t> threadList(threadCount);
    std::vector<int*> threadArgs(threadCount);

    resultValues.resize(threadCount, 0);
    unsigned int elementsPerThread = dataSize / threadCount;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < threadCount; ++i)
    {
        int start = i * elementsPerThread;
        int end = (i + 1) * elementsPerThread;
        threadArgs[i] = new int[3]{i, start, end};

        pthread_create(&threadId, nullptr, processData, threadArgs[i]);
        threadList[i] = threadId;
    }

    for (int i = 0; i < threadCount; ++i)
        pthread_join(threadList[i], nullptr);

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

    int finalResult = 0;
    for (int i = 0; i < threadCount; ++i)
        finalResult ^= resultValues[i];

    std::cout << "Final Result: " << finalResult << "\n";
    std::cout << "Time Elapsed: " << duration.count() << " ms\n";

    for (int i = 0; i < threadCount; ++i)
        delete[] threadArgs[i];

    return 0;
}
