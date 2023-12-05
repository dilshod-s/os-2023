#include <algorithm>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <random>
#include <vector>
unsigned int xor_result = 0;
std::default_random_engine generator;
std::uniform_int_distribution<unsigned int> distribution(0, 2000);

void *worker(void *data);

int main() {
  unsigned int N;
  std::cout << "Enter the number of elements \n";
  std::cin >> N;
  int ThreadsAmount;
  std::cout << "Enter the number of threads: \n ";
  std::cin >> ThreadsAmount;
  unsigned int for_each_thread = N / ThreadsAmount;
  std::vector<pthread_t> threads(ThreadsAmount);
  auto start = std::chrono::high_resolution_clock::now();
  unsigned int *args = new unsigned int{for_each_thread};
  for (int i = 0; i < ThreadsAmount; i++) {
    pthread_create(threadп[i], NULL, worker, args);
  }
  for (int i = 0; i < ThreadsAmount; i++) 
    pthread_join(threads[i], NULL);
    delete args;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken: " << duration.count() << " microseconds"
            << std::endl;
  std::cout << "XOR result: " << xor_result << std::endl;
  return 0;
}
void *worker(void *data) {
  unsigned int *args = static_cast<unsigned int *>(data);
  unsigned int range = *args;
  for (int i = 0; i < range; i++) {
    xor_result ^= distribution(generator);
  }
  pthread_exit(NULL);
}
