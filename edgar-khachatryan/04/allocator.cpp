#include <iostream>

constexpr size_t PGSIZE  = 256;   // 2 ^  8;
constexpr size_t MEMSIZE = 65536; // 2 ^ 16;
constexpr size_t PGCOUNT = 256;   // MEMSIZE / PGSIZE

struct Memory
{ char data[MEMSIZE]{}; };

struct MemoryAllocator
{
    MemoryAllocator(Memory* memory)
    { memory->data[0] = 1; }

    void* alloc(Memory* memory, size_t size)
    {
        size_t pagesToAllocate = static_cast<size_t>((size % PGSIZE) ? (size / PGSIZE + 1) : (size / PGSIZE));
        size_t currentCount = 0, i;

        for (i = 0; i < PGCOUNT; ++i)
        {
            if (memory->data[i] == 0)
                ++currentCount;
            else
            	currentCount = 0;
            
            if (currentCount == pagesToAllocate)
                break;
        }

        if (i == PGCOUNT || !i)
            return nullptr; // Allocation failed.
        else
        {
            size_t index = i - pagesToAllocate + 1;
            memory->data[index] = 1;
            for (size_t j = 1; j < pagesToAllocate; ++j)
                memory->data[index+j] = 2;
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
        for (size_t i = 1; i < PGCOUNT; ++i)
            memory->data[i] = 0;
    }

    void printPageInfo(Memory* memory, int lr, int rr)
    {
        if (lr > rr)
            std::swap(lr, rr);

        std::cout << "---------\n";
        for (int i = lr; i <= rr; ++i)
            std::cout << i << ":\t" << static_cast<int>(memory->data[i]) << "\n";
        std::cout << "---------\n";
    }

};

int main()
{
    Memory memory;
    MemoryAllocator allocator(&memory);
    std::cout << "Memory begin:\t\t" << static_cast<void*>(memory.data) << std::endl;

    allocator.printPageInfo(&memory, 0, 4);

    size_t s = 512;
    void* ptr1 = allocator.alloc(&memory, s);
    std::cout << "size: " << s << "\tptr1:\t" << ptr1 << std::endl;

    s = 1024;
    void* ptr2 = allocator.alloc(&memory, s);
    std::cout << "size: " << s << "\tptr2:\t" << ptr2 << std::endl;

    s = 64;
    void* ptr3 = allocator.alloc(&memory, s);
    std::cout << "size: " << s << "\tptr3:\t" << ptr3 << std::endl;

    s = 32;
    void* ptr4 = allocator.alloc(&memory, s);
    std::cout << "size: " << s << "\tptr4:\t" << ptr4 << std::endl;

    s = 0;
    void* ptr5 = allocator.alloc(&memory, s);
    std::cout << "size: " << s << "\t\tptr5:\t" << ptr5 << std::endl;

    allocator.printPageInfo(&memory, 0, 10);

    int freed_bytes = allocator.free(&memory, ptr2);
    std::cout << "ptr2 freed.\tBytes freed: " << freed_bytes << std::endl;
    allocator.printPageInfo(&memory, 0, 10);

    s = 512;
    void* ptr6 = allocator.alloc(&memory, s);
    std::cout << "size: " << s << "\tptr6:\t" << ptr6 << std::endl;
    allocator.printPageInfo(&memory, 0, 10);

    allocator.clean(&memory);
    std::cout << "allocator cleaned!" << std::endl;
    allocator.printPageInfo(&memory, 0, 4);


    return 0;
}

