#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 256
#define BLOCKS_COUNT 256

struct Memory {
    char buffer[BLOCK_SIZE*BLOCKS_COUNT];
};

void initializeMemory(struct Memory* mem) {
    memset(&mem->buffer, 0, BLOCK_SIZE*BLOCKS_COUNT);
    mem->buffer[0] = 1;
}

void* alloc_(struct Memory* mem, size_t size) {
    if (!mem || size == 0) {
        return NULL;
    }

    size_t blocksForAllocation = size / BLOCK_SIZE;
    if (size % BLOCK_SIZE > 0) {
        blocksForAllocation++;
    }

    size_t currentBlockCount = 0;
    for (size_t i = 0; i < BLOCKS_COUNT; i++) {
        if (mem->buffer[i] == 0) {
            ++currentBlockCount;
        }

        if (currentBlockCount == blocksForAllocation) {
            i -= blocksForAllocation - 1;

            for (size_t j = i; j < i + blocksForAllocation; j++) {
                if (j == i) {
                    mem->buffer[j] = 1;
                }
                else {
                    mem->buffer[j] = 2;
                }
            }

            return (mem->buffer + i*BLOCK_SIZE);
        }
    }

    return NULL;
}

size_t free_(struct Memory* mem, void* ptr)
{
    size_t index = ((uintptr_t)ptr - (uintptr_t)mem) / BLOCK_SIZE;

    if (((uintptr_t)ptr - (uintptr_t)mem ) % BLOCK_SIZE > 0
        || mem->buffer[index] == 0|| mem->buffer[index] == 2) {
        return 0;
    }

    size_t result = BLOCK_SIZE;

    mem->buffer[index] = 0;

    for (size_t i = index + 1; i < BLOCKS_COUNT; i++) {
        if (mem->buffer[i] == 2) {
            mem->buffer[i] = 0;
            result += BLOCK_SIZE;
        }
        else {
            break;
        }
    }

    return result;
}

void clean_(struct Memory* mem) {
    initializeMemory(mem);
    printf("Blocks cleared!\n");
}


int main() {
    struct Memory mems;
    initializeMemory(&mems);

    void* block1 = alloc_(&mems, 512);
    printf("Block 1: %p\n", block1);

    void* block2 = alloc_(&mems, 256);
    printf("Block 2: %p\n", block2);

    size_t bytesCleaned = free_(&mems, block1);
    printf("Block 1 freed: %zu bytes\n", bytesCleaned);

    void* block3 = alloc_(&mems, 10);
    printf("Block 3: %p\n", block3);

    bytesCleaned = free_(&mems, block3);
    printf("Block 3 freed: %zu bytes\n", bytesCleaned);

    clean_(&mems);

    return 0;
}

