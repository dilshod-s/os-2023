#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>

void calculate_xor_sum(std::vector<int>& nums, int start, int end, int& result) {
    for (int i = start; i < end; ++i) {
        result ^= nums[i];
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <number of threads>" << std::endl;
        return 1;
    }

    int num_threads = std::stoi(argv[1]);
    int N = 100000000;
    int chunk_size = N / num_threads;

    std::vector<int> nums(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    for (int i = 0; i < N; ++i) {
        nums[i] = dis(gen);
    }

    std::vector<std::thread> threads(num_threads);
    std::vector<int> results(num_threads);
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(calculate_xor_sum, std::ref(nums), i * chunk_size, (i + 1) * chunk_size, std::ref(results[i]));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    int final_result = 0;

    for (int i = 0; i < num_threads; ++i) {
        final_result ^= results[i];
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "XOR sum: " << final_result << std::endl;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    return 0;
}
