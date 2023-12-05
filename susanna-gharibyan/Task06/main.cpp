#include <chrono>
#include <iostream>
#include <pthread.h>
#include <random>
#include <vector>

std::vector<int> vector;
std::vector<int> numbers;

std::vector<int> Nvectors(int N) {
  std::vector<int> V;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);
  for (int i = 0; i < N; ++i) {
    V.push_back(dis(gen));
  }
  return V;
}

void *worker(void *arg) {
  int *args = static_cast<int *>(arg);
  int index = args[0]; // thread ID
  int N = args[1];     // total threads
  int K = args[2];     // data size
  int XOR = 0;

  int start, end;

  start = (index == 0) ? 0 : ((N / K) * index) + 1;
  end = (index == K - 1) ? (N - 1) : ((N / K) * (index + 1));

  for (int i = start; i <= end; i++)
    XOR ^= numbers[i];
  vector[index] = XOR;
  pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <N> <K>" << std::endl;
    exit(EXIT_FAILURE);
  }

  int N = std::stoi(argv[1]); // total number of random numbers
  int K = std::stoi(argv[2]); // number of threads

  numbers = Nvectors(N);
  std::vector<int *> args(K);
  std::vector<pthread_t> threads(K);
  pthread_t tid;
  vector.resize(K, 0);

  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < K; ++i) {
    args[i] = new int[3]{i, N, K};
    pthread_create(&tid, nullptr, worker, args[i]);
    threads[i] = tid;
  }

  for (int i = 0; i < K; ++i) {
    pthread_join(threads[i], nullptr);
  }

  auto stop = std::chrono::high_resolution_clock::now();

  auto totally =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  int result = 0;
  for (int i = 0; i < K; ++i) {
    result ^= vector[i];
  }
  std::cout << totally.count() << " microseconds\n";
  std::cout << "Result: " << result << "\n";

  for (int i = 0; i < K; ++i) {
    delete[] args[i];
  }
}
