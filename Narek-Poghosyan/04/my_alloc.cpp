#include <iostream>
#include <vector>
#include <cstdint>

constexpr size_t PAGE_SIZE = 256;
constexpr size_t MEMORY_SIZE = 65536;
constexpr size_t PAGE_COUNT = MEMORY_SIZE / PAGE_SIZE;

struct Memory {
    std::vector<char> data;

    Memory() : data(MEMORY_SIZE, 0) {
        data[0] = 1; // Mark first page as reserved
    }
};

struct MyAllocator {
    struct AllocationInfo {
        uint32_t size;
        bool isAllocated;
    };

    std::vector<AllocationInfo> allocationTable;

    MyAllocator(Memory* memory) : allocationTable(PAGE_COUNT, {0, false}) {
        allocationTable[0].isAllocated = true; // Mark first page as reserved
    }

    void* alloc(Memory* memory, size_t size) {
        size_t pagesToAllocate = (size + PAGE_SIZE - 1) / PAGE_SIZE;
        size_t currentPageCount = 0;
        size_t startPageIndex = 0;

        for (size_t i = 0; i < PAGE_COUNT; ++i) {
            if (!allocationTable[i].isAllocated) {
                if (currentPageCount == 0) {
                    startPageIndex = i;
                }
                ++currentPageCount;
            } else {
                currentPageCount = 0;
            }

            if (currentPageCount == pagesToAllocate) {
                break;
            }
        }

        if (currentPageCount != pagesToAllocate) {
            return nullptr; // Allocation failed
        }

        for (size_t j = startPageIndex; j < startPageIndex + pagesToAllocate; ++j) {
            allocationTable[j].isAllocated = true;
            allocationTable[j].size = size;
        }

        return static_cast<void*>(&memory->data[startPageIndex * PAGE_SIZE]);
    }

    int free(Memory* memory, void* ptr) {
        if (ptr == nullptr) {
            return 0;
        }

        auto* startPtr = static_cast<char*>(ptr);
        size_t pageIndex = (startPtr - &memory->data[0]) / PAGE_SIZE;
        uint32_t freedBytes = 0;

        if (pageIndex >= PAGE_COUNT || !allocationTable[pageIndex].isAllocated) {
            return 0; // Invalid pointer or already freed
        }

        while (allocationTable[pageIndex].isAllocated) {
            freedBytes += allocationTable[pageIndex].size;
            allocationTable[pageIndex].isAllocated = false;
            allocationTable[pageIndex].size = 0;
            ++pageIndex;
        }

        return freedBytes;
    }

    int clean() {
        int totalFreedBytes = 0;
        for (auto& info : allocationTable) {
            if (info.isAllocated) {
                totalFreedBytes += info.size;
                info.isAllocated = false;
                info.size = 0;
            }
        }
        return totalFreedBytes;
    }
};

int main() {
    Memory memory;
    MyAllocator allocator(&memory);
    std::cout << "Memory start:\t\t" << static_cast<void*>(&memory.data[0]) << std::endl;

    size_t size = 512;
    void* pointer1 = allocator.alloc(&memory, size);
    std::cout << "size: " << size << "\tpointer1:\t" << pointer1 << std::endl;

    size = 1024;
    void* pointer2 = allocator.alloc(&memory, size);
    std::cout << "size: " << size << "\tpointer2:\t" << pointer2 << std::endl;

    size = 64;
    void* pointer3 = allocator.alloc(&memory, size);
    std::cout << "size: " << size << "\tpointer3:\t" << pointer3 << std::endl;

    size = 32;
    void* pointer4 = allocator.alloc(&memory, size);
    std::cout << "size: " << size << "\tpointer4:\t" << pointer4 << std::endl;

    allocator.free(&memory, pointer2);
    allocator.clean();
    
    return 0;
}
