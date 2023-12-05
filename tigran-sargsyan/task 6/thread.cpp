#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <chrono>

std::vector<int> random_num(int n){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);
  std::vector<int> v(n);
  for(int i = 0; i < n; i++) {
    v[i] = dis(gen);
  }
  return v;
}

int xor_sum(std::vector<int> v, int start, int end, int& result){
  int sum = 0;
  for(int i = start; i < end; i++) {
    sum ^= v[i];
  }
  return sum;
}

int main(int argc,char **argv) {
  if(argc != 2){
    std::cerr << "Error";
  }
  int K = std::stoi(argv[1]);
  int N = 1000000000;
  int thread_num = N/K;
  std::vector<std::thread> threads(K);
  std::vector<int> v = random_num(N);
  std::vector<int> sums(K);
  
  auto start_time = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < K; i++) {
      threads[i] = std::thread(xor_sum, std::ref(v), i * thread_num, (i + 1) * thread_num, std::ref(sums[i]));
  }

  for (int i = 0; i < K; i++) {
      threads[i].join();
  }

  int final_result = 0;

  for (int i = 0; i < K; i++) {
      final_result ^= sums[i];
  }
  
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

  std::cout << "XOR sum: " << final_result << std::endl;
  std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
  return 0;
}
