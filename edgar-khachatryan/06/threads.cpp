#include <iostream>
#include <pthread.h>
#include <random>
#include <chrono>

                        // Use this values with N = 10 to test functionality of code. Answer should be -17.
                        // Also don't forget to turn off random number generation function
std::vector<int> nums;  // {1, 5, -3, 8, 20, -10, -15, 6, 7, 12};
std::vector<int> buffer;


void* worker(void* data);
void generateValues(std::vector<int>& arr, int N);


int main()
{
    int N = 10, K;

    std::cout << "Enter array elements count: ";
    std::cin >> N;

    std::cout << "Generating array with random values...\n\n";
    generateValues(nums, N);

    pthread_t tid;
    std::string input;

    std::vector<pthread_t> threads;
    std::vector<int*> args;

    while(true)
    {
        std::cout << "Enter the amount of threads (or /exit to end program): ";
        std::cin >> input;

        if (input == "/exit")
            break;
        else
            K = std::stoi(input);

        buffer.resize(K, 0);
        threads.resize(K, 0);
        args.resize(K, nullptr);

        std::cout << "Starting work...\n\n";

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < K; ++i)
        {
            args[i] = new int[3]{i, N, K};
            pthread_create(&tid, nullptr, worker, args[i]);
            threads[i] = tid;
        }

        for (int i = 0; i < K; ++i)
            pthread_join(threads[i], nullptr);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken for counting: " << duration.count() << " microseconds\n";

        int result = buffer[0];
        for (int i = 1; i < K; ++i)
            result ^= buffer[i];
        std::cout << "Result: " << result << "\n\n";

        for (int i = 0; i < K; ++i)
            delete[] args[i];

        buffer.clear();
        threads.clear();
    }

    return 0;
}


void* worker(void* data)
{
    int* args = static_cast<int*>(data);
    int index = args[0];
    int N = args[1];
    int K = args[2];

    int lr, rr;

    if (index == 0)
        lr = 0;
    else
        lr = ((N / K) * index) + 1;

    if (index == K - 1)
        rr = N - 1;
    else
        rr = (N / K) * (index + 1);

    int threadResult = 0;
    for (int i = lr; i <= rr; i++)
        threadResult ^= nums[i];
    buffer[index] = threadResult;

    pthread_exit(nullptr);
}

void generateValues(std::vector<int>& arr, int N)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(-1000, 1000);

    for (int i = 0; i < N; ++i)
        arr.push_back(dist(rd));
}
