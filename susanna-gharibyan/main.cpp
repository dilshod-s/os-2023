#include <iostream>
#include <cstring>
#include <cstdint>

constexpr size_t MEMSIZE = 65536;
constexpr size_t PGSIZE =  256; //the size of one page

struct Memory {
char buffer[MEMSIZE];
};

size_t indexaddres(size_t idx){
  return idx*PGSIZE;
  //this function returns the index
}
void initMem(struct Memory *mem) {
  std::memset(&mem->buffer, 0, MEMSIZE);
  //we set all the bytes to zero
  mem->buffer[0] = 1;//the first byte always has a value 1
}

void *alloc(Memory *mem, int size){
  
  int thenumofpgs=MEMSIZE/PGSIZE;//the number of pages we have
  int numofpgstoalloc=0;//the number of pages to alllocate
  int firstindex=-1;
  if(size%PGSIZE!=0){
    numofpgstoalloc=size/PGSIZE+1;
  }
  else if(size%PGSIZE==0){
    numofpgstoalloc=size/PGSIZE;
  }
  int count=0;
  int i=0;
  mem->buffer[0]=1;
  if (indexaddres(numofpgstoalloc) >= MEMSIZE) 
  {
      return nullptr; // Not enough space
  }
  
     for(i = 0; i<thenumofpgs; ++i)
     {
       if (i * PGSIZE >= MEMSIZE) { 
           break;                       
       }
       if(mem->buffer[i]==0)
       {
         //we keep the first address, that had value 0
          ++count;
       }
       else{
         count=0;
       }
       if(count==numofpgstoalloc)
       {
        break;
       }
     }       
  //if we dont have enough pgs free to allocate we must return nullptr 
     if(i==thenumofpgs){
       return nullptr;
     }
       if(count!=numofpgstoalloc){
          return nullptr;
       }
  //we allocate the pgs
  firstindex=i-numofpgstoalloc+1;
  if(numofpgstoalloc==1){
    mem->buffer[firstindex]=2;
    return static_cast<void*>(mem->buffer + PGSIZE*firstindex);
  }
  int c=0;
   for( c=0; c<numofpgstoalloc-1; ++c)
   {
     mem->buffer[c+firstindex]= 1;
   }
   mem->buffer[c+firstindex]= 2;
  //  size_t addr = indexaddres(firstindex);
    //return &mem->buffer[addr];
  return static_cast<void*>(mem->buffer + PGSIZE*firstindex);
}

int free(Memory * mem, void *ptr){
  size_t pageid=((char*)ptr-(char*)mem->buffer)/PGSIZE;
if(pageid==2){
  return -1;
}
  size_t freed=0;
  while(mem->buffer[pageid]==1){
    mem->buffer[pageid]=0;
    freed+=PGSIZE;
    ++pageid;
  }
if(mem->buffer[pageid]==2){
  mem->buffer[pageid]=0;
  freed+=PGSIZE;
}
  return freed;
}
void clean(Memory *mem){
  for(int i = 0; i<MEMSIZE; ++i){
    mem->buffer[i]=0;
  }
}
  
int main() {
  Memory mem;
    initMem(&mem); // Initialize the memory buffer
  int size=512;
    void* block1=alloc(&mem, size);
  if (block1 != nullptr) {
  
      std::cout << "Allocated block 1 of size " << size << " at address: " << block1 << std::endl;
  }
  
  int size2=798;
    void* block2=alloc(&mem, size2);
  if (block2 != nullptr) {
      std::cout << "Allocated block 2 of size " << size2 << " at address: " << block2 << std::endl;
  }
int size3=512;
  void* block3=alloc(&mem, size3);
  if (block3 != nullptr) {
      std::cout << "Allocated block 3 of size " << size3 << " at address: " << block3 << std::endl;
  }
  int size4=71;
  void* block4=alloc(&mem, size4);
  if (block3 != nullptr) {
      std::cout << "Allocated block 3 of size " << size4 << " at address: " << block4 << std::endl;
  }
  int freed_bytes1 = free(&mem, block1);
  if (freed_bytes1 > 0) {
    
      std::cout << "Freed block 1. Bytes freed: " << freed_bytes1 << std::endl;
  } else {
      std::cout << "Block 1 was not freed or invalid." << std::endl;
  }
  int freed_bytes2 = free(&mem, block2);
  if (freed_bytes2 > 0) {
      std::cout << "Freed block 2. Bytes freed: " << freed_bytes2 << std::endl;
  } else {
      std::cout << "Block 2 was not freed or invalid." << std::endl;
  }
  int freed_bytes3 = free(&mem, block3);
  if (freed_bytes3 > 0) {
      std::cout << "Freed block 3. Bytes freed: " << freed_bytes3 << std::endl;
  } else {
      std::cout << "Block 3 was not freed or invalid." << std::endl;
  }
  int freed_bytes4 = free(&mem, block4);
  if (freed_bytes4 > 0) {
      std::cout << "Freed block 4. Bytes freed: " << freed_bytes4 << std::endl;
  } else {
      std::cout << "Block 4 was not freed or invalid." << std::endl;
  }
  clean(&mem);
}