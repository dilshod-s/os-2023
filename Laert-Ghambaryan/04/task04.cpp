#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 256
#define BLOCKS_COUNT 256
#define DATA_SIZE (BLOCK_SIZE - sizeof(size_t) - sizeof(enum State) - 4) // 4 for alignment
#define META_SIZE (BLOCK_SIZE - DATA_SIZE)

enum State {
    NOT_ALLOCATED,
    ALLOCATED_FIRST,
    ALLOCATED_NOT_FIRST
};

struct MemoryBlock {
    enum State state;
    size_t size;
    // 4 bytes of alignment
    char data[DATA_SIZE];
};

struct Memory {
    struct MemoryBlock block[BLOCKS_COUNT];
};

void initializeMemory(struct Memory* mem) {
    for (int i = 0; i < BLOCKS_COUNT; i++) {
        mem->block[i].state = NOT_ALLOCATED;
        mem->block[i].size = 0;
    }
}

void* alloc_(struct Memory* mem, size_t size) {
    if (!mem || size == 0) {
        return NULL;
    }

    size_t blocksForAllocation = size / DATA_SIZE;
    if (size % DATA_SIZE > 0) {
        blocksForAllocation++;
    }

    size_t currentBlockCount = 0;
    for (size_t i = 0; i < BLOCKS_COUNT; i++) {
        if (mem->block[i].state == NOT_ALLOCATED) {
            ++currentBlockCount;
        }

        if (currentBlockCount == blocksForAllocation) {
            i -= blocksForAllocation - 1;

            for (size_t j = i; j < i + blocksForAllocation; j++) {
                if (j == i) {
                    mem->block[j].state = ALLOCATED_FIRST;
                }
                else {
                    mem->block[j].state = ALLOCATED_NOT_FIRST;
                }

                if (j == i + blocksForAllocation - 1) {
                    mem->block[j].size = size % DATA_SIZE;
                }
                else {
                    mem->block[j].size = DATA_SIZE;
                }
            }

            return mem->block[i].data;
        }
    }

    return NULL;
}

size_t free_(struct Memory* mem, void* ptr)
{
    size_t index = ((uintptr_t)ptr - (uintptr_t)mem - META_SIZE) / BLOCK_SIZE;

    if ((((uintptr_t)ptr - (uintptr_t)mem - META_SIZE) % BLOCK_SIZE) % BLOCK_SIZE > 0
        || mem->block[index].state == NOT_ALLOCATED|| mem->block[index].state == ALLOCATED_NOT_FIRST) {
        return 0;
    }

    size_t result = mem->block[index].size;

    mem->block[index].state = NOT_ALLOCATED;
    mem->block[index].size = 0;

    for (size_t i = index + 1; i < BLOCKS_COUNT; i++) {
        if (mem->block[i].state == ALLOCATED_NOT_FIRST) {
            mem->block[i].state = NOT_ALLOCATED;
            result += mem->block[i].size;
            mem->block[i].size = 0;
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

    bytesCleaned = free_(&mems, block2);
    printf("Block 2 freed: %zu bytes\n", bytesCleaned);

    clean_(&mems);

    return 0;
}

