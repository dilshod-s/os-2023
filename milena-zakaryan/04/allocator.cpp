#include <cstddef>
#include <iostream>
#include <cstring>

#define MEMSIZE 65536 // 2^16
#define BLOCKSIZE 256 // 2^8

struct Memory {
    char data[MEMSIZE];
};

void initializeMemory(Memory* mem) {
    memset(&mem->data, 0, MEMSIZE);
    mem->data[0] = 1;
}

void* alloc(Memory* mem, int size) {
    int blockCount = 0;
    if (size % BLOCKSIZE > 0)
        ++blockCount;
    blockCount += (size / BLOCKSIZE);

    int i;
    size_t currentCount = 0;
    for (i = 1; i < MEMSIZE / BLOCKSIZE; ++i) {
        if (mem->data[i] == 0)
            currentCount++;
        else
            currentCount = 0;

        if (currentCount == blockCount)
            break;
    }

    if (i == MEMSIZE / BLOCKSIZE)
        return nullptr;

    i = i - blockCount + 1;
    mem->data[i] = 1;
    for (int j = i + 1; j < blockCount + i; ++j)
        mem->data[j] = 2;

    char* tmp = mem->data;
    tmp += i * BLOCKSIZE;

    return tmp;
}

size_t free(Memory* mem, void* ptr) {
    size_t offset = (static_cast <char*>(ptr) - mem->data) % BLOCKSIZE;
    size_t index = (static_cast <char*>(ptr) - mem->data) / BLOCKSIZE;

    if (ptr == nullptr || offset > 0 || ptr == mem->data || mem->data[index] != 1)
        return 0;

    size_t freedBytes = BLOCKSIZE;

    mem->data[index] = 0;
    ++index;
    while (mem->data[index] == 2) {
        mem->data[index] = 0;
        freedBytes += BLOCKSIZE;
        ++index;
    }

    return freedBytes;
}

void clean(Memory* mem) {
    memset(&mem->data, 0, MEMSIZE);
    mem->data[0] = 1;
}

int main() {
    Memory memory;
    initializeMemory( & memory);
    std::cout << static_cast<void*>(memory.data) << "\n\n";

    void* ptr1 = alloc(&memory, 1024);
    void* ptr2 = alloc(&memory, 512);
    void* ptr3 = alloc(&memory, 128);

    size_t bytesFreed = free(&memory, ptr2);

    std::cout << ptr1 << "\n" << ptr2 << "\n" << ptr3 << "\n\n";
    std::cout << bytesFreed << "\n\n";

    void * ptr4 = alloc(&memory, 128);

    std::cout << ptr1 << "\n" << ptr4 << "\n" << ptr3 << "\n\n";

    bytesFreed = free(&memory, ptr4);

    std::cout << bytesFreed << "\n\n";

    clean(&memory);

    return 0;
}
