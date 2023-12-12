#include <iostream>

#define PGCOUNT 257
#define PGSIZE 256

struct Page{
  char arr[PGSIZE];
};

struct Memory{

    Page pages[PGCOUNT];
    Page &meta = pages[0];
};

char* mem_allocator(Memory* mem, std::size_t size){

    if(!mem || !size)
    {
        return NULL;
    }

    std::size_t count = size/PGSIZE;
    std::size_t current = 0;
    std::size_t first_page = 0;

    if( size % PGSIZE ){
        ++count;
    }

    for(std::size_t i = 1; i < PGCOUNT; ++i) {

        if (mem->meta.arr[i - 1] == 0) {

            ++current;

            if (current == count) {

                first_page = i - count + 1;
                break;
            }

        } else {
            current = 0;
        }

        if (i == PGCOUNT - 1) {

            return NULL;
        }

    }
    if(first_page == 0){
        return NULL;
    }

    for(std::size_t i = first_page; i < first_page + count; ++i){

        if(i == first_page){
          
            mem->meta.arr[i] = 1;
          
        }else{
          
            mem->meta.arr[i] = 2;
        }
    }
    return  mem->pages[first_page].arr;
}

void clean(Memory* mem){

    if(!mem){
        return;
    }

    for(std::size_t i = 0; i < PGCOUNT - 1; ++i){

        mem->meta.arr[i] = 0;
    }

}

 void* free(Memory* mem, void* ptr){

    if(!mem ||!ptr){
        return NULL;
    }

    std::size_t page_id = static_cast<std::size_t>(ptr) - static_cast<std::size_t>(mem->pages);
    page_id /= PGSIZE;
    
    if(mem->meta.arr[page_id] == 0){
        return NULL;
    } 
    
    mem->meta.arr[page_id] = 0;
    ++page_id;
    
    while((mem->meta.arr[page_id] != 0 && mem->meta.arr[page_id] != 1) && page_id != PGCOUNT )
    {
        mem->meta.arr[page_id++] = 0;
    }
    return ptr;

} 


int main() {


    return 0;}
