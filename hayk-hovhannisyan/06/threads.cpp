#include <iostream>
#include <pthread.h>
#include <chrono>
#include <vector>
#include <random>

constexpr const size_t N = 100'000'002;
unsigned long long int xor_sum = 0;

struct Range {
    size_t start;
    size_t end;
};

void* calculateXOR(void* arg) {
    Range* range = static_cast<Range*>(arg);
    size_t start = range->start;
    size_t end = range->end;
    unsigned long long int resLocal = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long int> dis(-100'000'000,100'000'000);

    for (size_t i = start; i < end; ++i) {
        const long long int o = dis(gen);
        resLocal ^= o;
    }
    xor_sum ^= resLocal;

    delete range; // Освобождаем память
    return nullptr;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <num_threads>" << std::endl;
        return 1;
    }

    size_t numofthreads = std::stoi(argv[1]);
    size_t chunkSize = N / numofthreads;
    std::vector<pthread_t> threads;

    auto startTime = std::chrono::high_resolution_clock::now();

    // Запускаем потоки
    for (size_t i = 0; i < numofthreads; ++i) {
        Range* range = new Range{i * chunkSize, (i + 1) * chunkSize};
        pthread_t thread;
        pthread_create(&thread, nullptr, calculateXOR, range);
        threads.push_back(thread);
    }

    // Ждем завершения всех потоков
    for (size_t i = 0; i < numofthreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Выводим результаты
    std::cout << "Total XOR: " << xor_sum << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
