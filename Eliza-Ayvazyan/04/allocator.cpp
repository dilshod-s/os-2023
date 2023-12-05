#include <iostream>
#include <cstring>

#define MEMSIZE (2 << 17)
#define PGSIZE (2 << 8)

struct Memory {
    char buffer[MEMSIZE];
};

void initMem(Memory *mem) {
    std::memset(&mem->buffer, 0, MEMSIZE);
    // The first block is allocated for the block index
    mem->buffer[0] = 1;
}

int index2address(int idx) {
    return idx * PGSIZE;
}

int address2index(int addr) {
    return addr / PGSIZE;
}

void *alloc(Memory *mem, size_t sz) {
    if (sz > MEMSIZE) {
        // exit(1);
        return nullptr;
    } else {
        int pageCount = sz/PGSIZE;
        if(sz%PGSIZE) {
            ++pageCount;
        }

        // Search for free space
        int i = 1;
        int freeCount = 0;
        for (; i < PGSIZE; ++i) {
            if (mem->buffer[i] == 0) {
                ++freeCount;
            } else {
                freeCount = 0;
            }
            if (freeCount == pageCount) {
                break;
            }
        }

        // Mark space as allocated
        i = i - pageCount + 1;
        int ind = i;
        for(int j = 0; j < pageCount; ++j) {
            mem->buffer[i++] = pageCount;
        }

        // Return address
        int addr = index2address(ind);
        return &mem->buffer[addr];
    }
}

int free(Memory *mem, void *ptr) {
    int  freedBytes = 0;
    if ((static_cast<char*>(ptr) - static_cast<char*>(mem->buffer)) % PGSIZE || ptr == mem->buffer) {
        return -1;
    }

    int index = address2index(
            static_cast<int>((size_t)ptr - (size_t)mem->buffer)
    );

    int pageCount = mem->buffer[index];
    int i = index - 1;
    int count = 0;
    while(mem->buffer[i] == pageCount) {
        ++count;
        --i;
    }
    if(count % pageCount) {
        return -1;
    } else {
        for (int i = 0; i < pageCount; ++i) {
            mem->buffer[index+i] = 0;
            freedBytes += PGSIZE;
        }
    }

    return freedBytes;
}

void clean(Memory* memory)
{
    for (size_t i = 1; i < PGSIZE; ++i)
        memory->buffer[i] = 0;
}


int main() {
    Memory memory;
    initMem(&memory);

    size_t size = 32;
    void* ptr = alloc(&memory, size);

    size = 1024;
    void* ptr1 = alloc(&memory, size);

    size = 2048;
    void* ptr2 = alloc(&memory, size);

    int freed = free(&memory, ptr1);
    std::cout << freed << std::endl;

    clean(&memory);

    return 0;
}


