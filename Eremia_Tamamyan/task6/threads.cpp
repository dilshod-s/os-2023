#include <algorithm>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <random>
#include <vector>



unsigned int xor_result = 0;
std::mt19937 generator;  // Измененный генератор
std::uniform_int_distribution<unsigned int> distribution(0, 2000);
std::vector<unsigned int> local_xors;
void *worker(void *data);

int main() {
  unsigned int N = 100000000;

  int ThreadsAmount;
  std::cout << "Enter the number of threads: \n ";
  std::cin >> ThreadsAmount;
  local_xors.resize(ThreadsAmount);
  unsigned int for_each_thread = N / ThreadsAmount;
  std::vector<pthread_t> threads(ThreadsAmount);
  auto start = std::chrono::high_resolution_clock::now();

  for (unsigned int i = 0; i < ThreadsAmount; i++) {
    unsigned int *args = new unsigned int[2]{i, for_each_thread};
    pthread_create(&threads[i], NULL, worker, args);
  }
  
  for (int i = 0; i < ThreadsAmount; i++) {
    pthread_join(threads[i], NULL);
  }
  auto end = std::chrono::high_resolution_clock::now();
  
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
  for(auto i: local_xors)
  {
    xor_result ^= i;
  }
  std::cout << "XOR result: " << xor_result << std::endl;

  return 0;
}

void *worker(void *data) {
  unsigned int *args = static_cast<unsigned int *>(data);
  unsigned int range = args[1];
  unsigned int index = args[0];
  unsigned int local_xor_result = 0;

  for (int i = 0; i < range; i++) {
    local_xor_result ^= distribution(generator);
  }
  local_xors[index]=local_xor_result;
  
  delete[] args;
  pthread_exit(NULL);
}
