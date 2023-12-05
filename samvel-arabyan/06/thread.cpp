#include <iostream>
#include <pthread.h>
#include <chrono>
#include <cstdlib>
#include <vector>

constexpr const size_t N = 100'000'002;
size_t xor_sum = 0;

void* calculateXOR(void* arg) {
    size_t* range = static_cast<size_t*>(arg);
    size_t start = range[0];
    size_t end = range[1];
    size_t resLocal = 0;
    
    for (size_t i = start; i < end; ++i) {
        const size_t o = std::rand();
        resLocal ^= o;
    }
    xor_sum ^= resLocal;
    delete [] range;
    
    return nullptr;
}

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <num_threads>" << std::endl;
        return 1;
    }

    size_t numofthreads = std::stoi(argv[1]);
    size_t chunkSize = N / numofthreads;
    std::vector<pthread_t> threads(numofthreads);
    
    auto startTime = std::chrono::high_resolution_clock::now();

    // Запускаем потоки
    for (int i = 0; i < numofthreads; ++i) {
        size_t* range = new size_t[2];
        range[0] = i * chunkSize;
        range[1] = (i + 1) * chunkSize;
        pthread_create(&threads[i], nullptr, calculateXOR, range);
    }

    // Ждем завершения всех потоков
    for (int i = 0; i < numofthreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // Вычисляем общую сумму
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Выводим результаты
    std::cout << "Total XOR: " << xor_sum << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}