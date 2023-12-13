#include <iostream>

constexpr size_t PGSIZE  = 256;
constexpr size_t MEMORYSIZE = 65536;


struct Memory
{ 
    char data[MEMORYSIZE]{}; 
};

void init(Memory* memory)
{
    memory->data[0] = 1;
    for (size_t i = 1; i < MEMORYSIZE / PGSIZE; ++i)
        memory->data[i] = 0;
}

void *alloc(Memory* memory, size_t size)
{
    size_t pagesToAllocate;
    if (size % PGSIZE) {
        pagesToAllocate = static_cast<size_t>(size / PGSIZE + 1);
    }
    else {
        pagesToAllocate = static_cast<size_t>(size / PGSIZE);
    }
    size_t currentCount = 0;
    size_t i;

    for (i = 0; i < MEMORYSIZE / PGSIZE; ++i)
    {
        if (memory->data[i] == 0)
            ++currentCount;
        else
            currentCount = 0;
        
        if (currentCount == pagesToAllocate)
            break;
    }

    if (i == MEMORYSIZE / PGSIZE || !i)
        return nullptr;
    else
    {
        size_t index = i - pagesToAllocate + 1;
        memory->data[index] = 1;
        for (size_t j = 1; j < pagesToAllocate; ++j) {
            memory->data[index + j] = 2;
        }
        return static_cast<void*>(memory->data + PGSIZE*index);
    }
}

int free(Memory* memory, void* ptr)
{
    long pageid = static_cast<char*>(ptr) - static_cast<char*>(memory->data);
    auto offset = pageid % PGSIZE;
    pageid = pageid / static_cast<long>(PGSIZE);

    if (ptr == memory->data || offset || memory->data[pageid] != 1)
        return 0;

    size_t bytesFreed = PGSIZE;
    memory->data[pageid] = 0;
    ++pageid;

    while(memory->data[pageid] == 2)
    {
        bytesFreed += PGSIZE;
        memory->data[pageid] = 0;
        ++pageid;
    }

    return bytesFreed;
}

void clean(Memory* memory)
{
    for (size_t i = 1; i < MEMORYSIZE / PGSIZE; ++i)
        memory->data[i] = 0;
}


int main()
{
    Memory memory;
    init (&memory);

    std::cout << "Memory:\t\t\t" << static_cast<void*>(memory.data) << "\n";

    size_t size = 512;
    void* p1 = alloc(&memory, size);
    std::cout << "size: " << size << "\tp1:\t" << p1 << "\n";

    size = 1030;
    void* p2 = alloc(&memory, size);
    std::cout << "size: " << size << "\tp2:\t" << p2 << "\n";

    return 0;
}

