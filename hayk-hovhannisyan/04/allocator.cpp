#include <iostream>
#include <string.h>

#define MEMSIZE (1 << 16)
#define PGSIZE (1 << 8)

struct Memory {
    char buffer[MEMSIZE];
};

void initMem(struct Memory *mem) {
    memset(mem->buffer, 0, MEMSIZE);    
    mem->buffer[0] = 1;
}

int index2address(int idx) {
    return idx * PGSIZE;
}

int address2index(int addr) {
    return addr / PGSIZE;
}

void *alloc(struct Memory *mem, size_t sz) {
    if (sz > PGSIZE) {
        int count_of_pages = sz / PGSIZE;
        int count_of_emptypgs = 0;
        bool found_sequence = false;                
        int i = 1;

        for (; i < MEMSIZE - 1; ++i) {
            if (mem->buffer[i] == 0) {
                ++count_of_emptypgs;
            } else {
                count_of_emptypgs = 0;
            }

            if (count_of_emptypgs == count_of_pages) {
                found_sequence = true;
                break;
            }
        }

        if (found_sequence) {            
            for (int l = i - count_of_pages + 1; l <= i; ++l) {
                mem->buffer[l] = 1;
            }            
            int addr = index2address(i - count_of_pages + 1);
            return &mem->buffer[addr];
        } else {            
            return NULL;
        }
    }
     else {
        int i = 1;
        for (; i < MEMSIZE; i++) {
            if (mem->buffer[i] == 0) {
                break;
            }
        }
        mem->buffer[i] = 1;        
        int addr = index2address(i);
        return &mem->buffer[addr];
    }
}


int clean(struct Memory *mem) {
    memset(&(mem->buffer[1]), 0, MEMSIZE - 1);
    return 0;
}

int free(Memory* mem,Memory* ptr){
    if ((size_t) ptr % PGSIZE != 0) {
        return -1;
    }
    int index = address2index((int) ((char*)ptr -  mem->buffer));
    int i = index;
    while(i < MEMSIZE && mem->buffer[i]!=0 ){
        mem->buffer[i] = 0;
        ++i;
    }
    return 0;
}
            
int main() {
    struct Memory mem;
    initMem(&mem);

    void *ptr = &mem.buffer;
    printf("Payload // pointer = %lx\n", (size_t) mem.buffer);

    ptr = alloc(&mem, 128);
    printf("Payload // pointer = %lx\n", (size_t) ptr);
    

    ptr = alloc(&mem, 256);
    printf("Payload // pointer = %lx\n", (size_t) ptr);
    

    ptr = alloc(&mem, 1);
    printf("Payload // pointer = %lx\n", (size_t) ptr);

    return 0;
}

