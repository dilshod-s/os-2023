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
struct ThreadData {
    std::vector<int>& nums;
    int start_index;
    int end_index;
    int& result;
};

void* calculate_xor_sum_pthread(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);

    std::vector<int>& nums = data->nums;
    int start_index = data->start_index;
    int end_index = data->end_index;
    int& result = data->result;

    calculate_xor_sum(nums, start_index, end_index, result);

    pthread_exit(NULL);
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

    pthread_t threads[num_threads];
    std::vector<int> results(num_threads);
    std::vector<ThreadData> thread_data(num_threads);
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        thread_data[i] = {nums, i * chunk_size, (i + 1) * chunk_size, results[i]};
        int create_result = pthread_create(&threads[i], NULL, calculate_xor_sum_pthread, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
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
