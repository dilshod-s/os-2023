#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

void calculate_xor(const std::vector<unsigned int>& numbers, int start, int end, unsigned int& xor_result) {
    xor_result = 0;
    for (int i = start; i < end; ++i) {
        xor_result ^= numbers[i];
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <N> <K>\n";
        return 1;
    }

    long N = std::stol(argv[1]);
    int K = std::stoi(argv[2]);
    std::vector<unsigned int> numbers(N);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<unsigned int> dist;
    for (auto& num : numbers) {
        num = dist(rng);
    }

    std::vector<std::thread> threads;
    std::vector<unsigned int> results(K, 0);
    int segment_size = N / K;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < K; ++i) {
        int start = i * segment_size;
        int end = (i != K - 1) ? (i + 1) * segment_size : N;
        threads.emplace_back(calculate_xor, std::ref(numbers), start, end, std::ref(results[i]));
    }

    unsigned int total_xor = 0;

    for (int i = 0; i < K; ++i) {
        threads[i].join();
        total_xor ^= results[i];
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Total XOR: " << total_xor << "\n";
    std::cout << "Time taken: " << duration.count() << " seconds\n";

    return 0;
}
