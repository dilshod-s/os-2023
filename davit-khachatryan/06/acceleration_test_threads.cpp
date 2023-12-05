#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <pthread.h>

constexpr const unsigned long long int N = 100'000'001;

unsigned long long int xor_sum = 0;
pthread_mutex_t xor_sum_mutex;

/**
 * @brief Thread function to calculate local XOR sum.
 * @param arg The range of indices for the thread to process.
 * @return nullptr
 */

void* thread_func(void* arg) {
    unsigned int* range = static_cast<unsigned int*>(arg);
    unsigned int start = range[0];
    unsigned int end = range[1];
    unsigned long long int local_xor_sum = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-10000, 10000);

    for (unsigned int i = start; i < end; i++) {
        unsigned int k = dis(gen);
        local_xor_sum ^= k;
    }

    pthread_mutex_lock(&xor_sum_mutex);
    xor_sum ^= local_xor_sum;    
    pthread_mutex_unlock(&xor_sum_mutex);

    delete[] range;

    return nullptr;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./program_name <num_threads>" << "\n";
        return 1;
    }

    unsigned int num_threads = std::stoi(argv[1]);
    unsigned int nums_per_thread = N / num_threads;

    pthread_mutex_init(&xor_sum_mutex, nullptr);

    std::vector<pthread_t> threads;
    auto start_time = std::chrono::high_resolution_clock::now();

    for (unsigned int i = 0; i < num_threads; i++) {
        unsigned int* range = new unsigned int[2];
        range[0] = i * nums_per_thread;
        range[1] = (i + 1) * nums_per_thread;

        pthread_t thread;
        pthread_create(&thread, nullptr, thread_func, range);
        threads.push_back(thread);
    }

    std::cout << "Calculating XOR sum, this will take a while if you run program on a single thread..." << "\n";
    for (auto& thread : threads) {
        pthread_join(thread, nullptr);
    }

    pthread_mutex_destroy(&xor_sum_mutex);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "XOR sum: " << xor_sum << "\n";
    std::cout << "Time taken: " << duration.count() << " milliseconds" << "\n";

    return 0;
}