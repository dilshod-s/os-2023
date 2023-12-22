#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include <pthread.h>


std::mt19937 gen;                              //generator (Mersenne Twister)
std::uniform_int_distribution<> dis(1, 2000);  //ravnomerno raspredelyaet
std::vector<unsigned int> v;                         
unsigned int xor_sum = 0;
unsigned int n = 100000000;
void *worker(void *data);                      //opredelim pozje

int main(){
    
    unsigned int k;                            //number of threads
    std::cout << "How many threads do you want to use? \n ";
    std::cin >> k;
    v.resize(k);
    unsigned int one_thread_job = n / k;
    std::vector<pthread_t> threads(k);
    auto start = std::chrono::high_resolution_clock::now();

    for(unsigned int i = 0; i < k; i++){
        
        unsigned int *args = new unsigned int[2]{i, one_thread_job};
        pthread_create(&threads[i], NULL, worker, args);
    }

    for(unsigned int i = 0; i < k; i++){
        
        pthread_join(threads[i], NULL);
    }
  
    
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    for(unsigned int i = 0; i < v.size(); i++){
        xor_sum ^= v[i];
        
    }
    std::cout << "Result: " << xor_sum << std::endl;
    
    return 0;
}

void *worker(void *data){
    
  unsigned int *args = static_cast<unsigned int *>(data);
  unsigned int range = args[1];
  unsigned int index = args[0];
  unsigned int xor_result = 0;

  for (int i = 0; i < range; i++) {
    xor_result ^= dis(gen);
  }
  
  v[index] = xor_result;
  
  delete[] args;
  pthread_exit(NULL);
}
