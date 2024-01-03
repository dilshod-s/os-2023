#include <iostream>
#include <cstddef>

struct MemoryBlock {
    size_t size;
    bool isFree;
    MemoryBlock* next;
};

struct Memory {
    void* start;
    size_t totalSize;
    MemoryBlock* freeList;
};

void initializeMemory(Memory* mem, size_t size) {
    mem->start = ::operator new(size);
    mem->totalSize = size;
    mem->freeList = nullptr;
    MemoryBlock* initialBlock = static_cast<MemoryBlock*>(mem->start);
    initialBlock->size = size;
    initialBlock->next = nullptr;
    mem->freeList = initialBlock;
}

void* alloc(Memory* mem, size_t size) {
    MemoryBlock* current = mem->freeList;
    MemoryBlock* prev = nullptr;

    while (current) {
        if (current->size >= size) {
            if (current->size > size) {
                MemoryBlock* newBlock = reinterpret_cast<MemoryBlock*>(reinterpret_cast<char*>(current) + size);
                newBlock->size = current->size - size;
                newBlock->next = current->next;

                if (prev) {
                    prev->next = newBlock;
                }
                else {
                    mem->freeList = newBlock;
                }

                current->size = size;
                current->next = nullptr;
            }
            return reinterpret_cast<void*>(current + 1);
        }

        prev = current;
        current = current->next;
    }

    return nullptr;
}

void free(Memory* mem, void* ptr) {
    MemoryBlock* block = static_cast<MemoryBlock*>(ptr) - 1;

    if (!block || !block->isFree) {
        return;
    }

    block->isFree = true;

    MemoryBlock* current = mem->freeList;
    while (current) {
        if (current->next == block || (reinterpret_cast<char*>(current) + current->size) == reinterpret_cast<char*>(block)) {
            current->size += block->size;
            current->next = block->next;
            block = current;
        }
        current = current->next;
    }

    if (block != mem->freeList) {
        block->next = mem->freeList;
        mem->freeList = block;
    }
}


int clean(Memory* mem) {
    ::operator delete(mem->start);
    mem->start = nullptr;
    mem->totalSize = 0;
    mem->freeList = nullptr;

    return 0;
}

int main() {
    Memory myMemory;
    initializeMemory(&myMemory, 1024);
    void* ptr = alloc(&myMemory, 128);
    if (ptr) {
        clean(&myMemory);
    }
    return 0;
}
