#include <iostream>
#include <pthread.h>
#include <random>
#include <chrono>

std::vector<int> numbers;
std::vector<int> answers;

void* thread_func(void* arg)
{
    unsigned int* range = static_cast<unsigned int*>(arg);
    unsigned int index = range[0];
    unsigned int start = range[1];
    unsigned int end = range[2];
    unsigned long long int local_sum = 0;

    for (unsigned int i = start; i < end; i++)
        local_sum ^= numbers[i];

    answers[index] = local_sum;    

    return nullptr;
}


void generateValues(int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-10000, 10000);

    for (int i = 0; i < N; ++i)
        numbers.push_back(dis(gen));
}


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " < N >  < K >" << "\n";
        return 1;
    }
    int N = std::stoi(argv[1]), K = std::stoi(argv[2]);

    generateValues(N);

    pthread_t tid;
    std::vector<pthread_t> threads(K);
    std::vector<int*> args(K);

    answers.resize(K, 0);
    unsigned int nums_per_thread = N / K;

    auto time_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < K; ++i)
    {
        int start = i * nums_per_thread;
        int end = (i + 1) * nums_per_thread;
	args[i] = new int[3]{i, start, end};
   	pthread_create(&tid, nullptr, thread_func, args[i]);
   	threads[i] = tid;
    }

    for (int i = 0; i < K; ++i)
   	pthread_join(threads[i], nullptr);
    auto time_stop = std::chrono::high_resolution_clock::now();
    auto time_duration = std::chrono::duration_cast<std::chrono::microseconds>(time_stop - time_start);
    
    int finalAnswer = 0;
    for (int i = 0; i < K; ++i)
   	finalAnswer ^= answers[i];
   	
    std::cout << "Answer: " << finalAnswer << "\n";
    std::cout << "Time taken: " << time_duration.count() << " ms\n";

    for (int i = 0; i < K; ++i)
   	delete[] args[i];

    return 0;
}


