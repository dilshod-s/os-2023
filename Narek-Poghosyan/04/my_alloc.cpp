#include <iostream>
#include <vector>
#include <unordered_map>

constexpr size_t PAGE_SIZE = 256;
constexpr size_t MEMORY_SIZE = 65536;
constexpr size_t PAGE_COUNT = MEMORY_SIZE / PAGE_SIZE;

struct Memory {
    std::vector<char> data;

    Memory() : data(MEMORY_SIZE, 0) {
        // Mark first page as reserved for metadata (hash-map)
        data[0] = 1;
    }
};

struct PageMetadata {
    size_t size;
    void* address;
};

struct MyAllocator {
    std::unordered_map<void*, PageMetadata> metadata;

    MyAllocator(Memory* memory) {
        // Mark first page as reserved for metadata (hash-map)
        metadata[&memory->data[0]] = {PAGE_SIZE, nullptr};
    }

    void* alloc(Memory* memory, size_t size) {
        size_t pagesToAllocate = (size + PAGE_SIZE - 1) / PAGE_SIZE;
        size_t currentPageCount = 0;
        size_t startPageIndex = 0;

        // Find consecutive free pages for allocation
        for (size_t i = 1; i < PAGE_COUNT; ++i) {
            if (memory->data[i * PAGE_SIZE] == 0) {
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

        // Mark pages as allocated and update metadata
        void* allocatedAddress = static_cast<void*>(&memory->data[startPageIndex * PAGE_SIZE]);
        for (size_t j = startPageIndex; j < startPageIndex + pagesToAllocate; ++j) {
            memory->data[j * PAGE_SIZE] = 1; // Mark page as allocated
            metadata[&memory->data[j * PAGE_SIZE]] = {size, allocatedAddress};
        }

        return allocatedAddress;
    }

    int free(Memory* memory, void* ptr) {
        auto it = metadata.find(ptr);
        if (it == metadata.end() || it->second.address != ptr) {
            return 0; // Invalid pointer or not found in metadata
        }

        size_t pagesFreed = it->second.size / PAGE_SIZE + (it->second.size % PAGE_SIZE != 0);
        for (size_t i = 0; i < pagesFreed; ++i) {
            memory->data[(reinterpret_cast<char*>(ptr) - &memory->data[0]) / PAGE_SIZE * PAGE_SIZE] = 0; // Mark page as free
            metadata.erase(ptr);
            ptr = reinterpret_cast<void*>(reinterpret_cast<char*>(ptr) + PAGE_SIZE);
        }

        return it->second.size;
    }

    void printMemoryMap() {
        for (const auto& entry : metadata) {
            std::cout << "Address: " << entry.second.address << "\tSize: " << entry.second.size << " bytes\n";
        }
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

    allocator.printMemoryMap();

    allocator.free(&memory, pointer2);
    std::cout << "Pointer2 freed." << std::endl;

    allocator.printMemoryMap();

    return 0;
}
