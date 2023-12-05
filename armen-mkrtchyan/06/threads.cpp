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
    
    for(int i = 0; i < n; i++){
        v[i] = dis(gen);
    }
    
    return v;
}

int xor_sum(std::vector<int> v, int start, int end, int& result){
    
  int sum = 0;
  
  for(int i = start; i < end; i++){
      
    sum ^= v[i];
  }
  
  return sum;
}

int main(int argc,char **argv){
    
    if(argc != 2){ std::cerr << "Error"; }
  
    unsigned int k = std::stoi(argv[1]);
    unsigned int n = 1000000000;
    unsigned int thread_num = n/k;
    std::vector<std::thread> threads(k);
    std::vector<int> v = random_num(n);
    std::vector<int> sums(k);
    int answer = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i < k; i++){
        
        threads[i] = std::thread(xor_sum, std::ref(v), i * thread_num, (i + 1) * thread_num, std::ref(sums[i]));
        
    }

    for(int i = 0; i < k; i++){
        
        threads[i].join();
        
    }

    for(int i = 0; i < k; i++){
        
        answer ^= sums[i];
    }
  
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    std::cout << "Result: " << answer << std::endl;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    
    return 0;
}