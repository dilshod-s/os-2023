#include <iostream>
#include <cstring>

#define MEMORY_SIZE 65536 // 2^16
#define BLOCK_SIZE 256 // 2^8

struct StorageUnit {
    char data[MEMORY_SIZE];
};

void initializeStorage(StorageUnit* storage) {
    memset(&storage->data, 0, MEMORY_SIZE);
    storage->data[0] = 'A';
}

void* allocateMemory(StorageUnit* storage, int size) {
    int blockCount = size / BLOCK_SIZE + (size % BLOCK_SIZE != 0 ? 1 : 0);

    int i;
    size_t currentBlockCount = 0;
    for (i = 1; i < MEMORY_SIZE / BLOCK_SIZE; ++i) {
        if (storage->data[i] == 0)
            currentBlockCount++;
        else
            currentBlockCount = 0;

        if (currentBlockCount == blockCount)
            break;
    }

    if (i == MEMORY_SIZE / BLOCK_SIZE)
        return nullptr;

    i = i - blockCount + 1;
    storage->data[i] = 'A';
    for (int j = i + 1; j < blockCount + i; ++j)
        storage->data[j] = 'B';

    char* allocatedMemory = storage->data;
    allocatedMemory += i * BLOCK_SIZE;

    return allocatedMemory;
}

size_t deallocate(StorageUnit* storage, void* ptr) {
    size_t offset = (static_cast<char*>(ptr) - storage->data) % BLOCK_SIZE;
    size_t index = (static_cast<char*>(ptr) - storage->data) / BLOCK_SIZE;

    if (ptr == nullptr || offset > 0 || ptr == storage->data || storage->data[index] != 'A')
        return 0;

    size_t freedBytes = BLOCK_SIZE;

    storage->data[index] = 0;
    ++index;
    while (storage->data[index] == 'B') {
        storage->data[index] = 0;
        freedBytes += BLOCK_SIZE;
        ++index;
    }

    return freedBytes;
}

void clearStorage(StorageUnit* storage) {
    memset(&storage->data, 0, MEMORY_SIZE);
    storage->data[0] = 'A';
}

int main() {
    StorageUnit memory;
    initializeStorage(&memory);
    std::cout << static_cast<void*>(memory.data) << "\n\n";

    void* pointer1 = allocateMemory(&memory, 1024);
    void* pointer2 = allocateMemory(&memory, 512);
    void* pointer3 = allocateMemory(&memory, 128);

    size_t bytesFreed = deallocate(&memory, pointer2);

    std::cout << pointer1 << "\n" << pointer2 << "\n" << pointer3 << "\n\n";
    std::cout << bytesFreed << "\n\n";

    void* pointer4 = allocateMemory(&memory, 128);

    std::cout << pointer1 << "\n" << pointer4 << "\n" << pointer3 << "\n\n";

    bytesFreed = deallocate(&memory, pointer4);

    std::cout << bytesFreed << "\n\n";

    clearStorage(&memory);

    return 0;
}
