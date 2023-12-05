#include <iostream>
#include <pthread.h>
#include <random>
#include <chrono>
#include <vector>
#include <thread>

std::vector<int> numbers;
std::vector<int> results;

struct Thread {
    int index;
    int start;
    int end;

    Thread(int i, int N, int K) : index(i) {
        int x = N/K;

        if (index == 0) {
            start = 0;
        } else {
            start = x * index;
        }
        if (index == K - 1) {
            end = N;
        } else {
            end = x * (index + 1);
        }
    }
};

void generate (int N) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator

    // Generate N random numbers and fill the vector
    std::uniform_int_distribution<int> distribution(-1000, 1000);
    for (int i = 0; i < N; ++i) {
        int randomNumber = distribution(gen);
        numbers.push_back(randomNumber);
    }
}

void* xorWorker(void* args) {
    auto data = static_cast<Thread*>(args);

    int res = 0;
    for (int i = data->start; i < data->end; ++i) {
        res ^= numbers[i];
    }
    results[data->index] = res;

    pthread_exit(nullptr);
}

int main() {
    int N, K;
    std::cin >> N;
    std::cin >> K;

    generate(N);
    std::vector<Thread*> args;

    pthread_t tid;
    std::vector<pthread_t> threads;

    results.resize(K, 0);
    threads.resize(K, 0);
    args.resize(K, nullptr);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < K; ++i) {
        args[i] = new Thread(i, N, K);
        pthread_create(&tid, nullptr, xorWorker, args[i]);
        threads[i] = tid;
    }

    for (int i = 0; i < K; ++i) {
        pthread_join(threads[i], nullptr);
    }
    auto stop = std::chrono::high_resolution_clock::now();

    int final_result = 0;
    for (int i = 0; i < K; ++i) {
        final_result ^= results[i];
    }

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time: " << duration.count() << std::endl;
    std::cout << "result: " << final_result << std::endl;

    for (int i = 0; i < K; ++i) {
        delete[] args[i];
    }

    return 0;
}
