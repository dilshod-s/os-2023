#include <iostream>
#include <array>
#include <cstring>

constexpr std::size_t metaData = 12;
constexpr std::size_t blockSize = 256;
constexpr std::size_t blockCount = 128;
constexpr std::size_t charArrSize = blockSize - metaData;

struct alignas(8) MemoryBlock {
    enum class State {
        Active, Passive
    } state;
    std::size_t bytesAllocated;
    char data[charArrSize];
};

struct Memory {
    std::array<MemoryBlock, blockCount> blocks;
};

class DummyAllocator {
public:
    DummyAllocator() {
    }

    void* allocate(Memory* memory, std::size_t size) {
        if (size == 0) { return nullptr; }

        std::size_t remainingSize = size;
        void* allocatedMemory = nullptr;

        for (std::size_t i = 0; i < memory->blocks.size(); ++i) {
            if (remainingSize == 0) {
                break;
            }
            if (memory->blocks[i].state == MemoryBlock::State::Passive) {
                if (remainingSize <= (blockSize - memory->blocks[i].bytesAllocated)) {
                    memory->blocks[i].state = MemoryBlock::State::Active;
                    memory->blocks[i].bytesAllocated += remainingSize;
                    allocatedMemory = memory->blocks[i].data + metaData;
                    remainingSize = 0;
                } else {
                    memory->blocks[i].state = MemoryBlock::State::Active;
                    remainingSize -= (blockSize - memory->blocks[i].bytesAllocated);
                    memory->blocks[i].bytesAllocated = blockSize;
                    allocatedMemory = memory->blocks[i].data + metaData;
                }
            }
        }
        return allocatedMemory;
    }

    int free(Memory* memory, void* ptr) {
        char* charPtr = static_cast<char*>(ptr);
        for (auto& block : memory->blocks) {
            char* blockStart = block.data;
            char* blockEnd = blockStart + blockSize - metaData;
            if (charPtr >= blockStart && charPtr < blockEnd) {
                block.state = MemoryBlock::State::Passive;
                block.bytesAllocated = 0;
                std::memset(block.data, 0, charArrSize);
                return 0;
            }
        }
        return -1;
    }

    void clean(Memory* memory) {
        initialize(memory);
    }

    void initialize(Memory* memory) {
        for (auto& block : memory->blocks) {
            block.bytesAllocated = 0;
            block.state = MemoryBlock::State::Passive;
            std::memset(block.data + metaData, 0, charArrSize);
        }
    }

    void setBytesAllocated(MemoryBlock* block)
    {
        for (auto i = 0; i < block->bytesAllocated; ++i )
        {
            block->data[i] = '1';
        }
    }

    void printActiveBlocks(Memory* memory) {
        int count = 0;
        for ( auto i = 0; i < memory->blocks.size(); ++i) {
            std::cout << memory->blocks[i].bytesAllocated <<", ";
        }
    }

    ~DummyAllocator() = default;
};

int main() {
    Memory mem;
    DummyAllocator allocator;

    allocator.initialize(&mem);
    void* ptr1 = allocator.allocate(&mem, 845);
    allocator.printActiveBlocks(&mem);
    std::cout << "\n";

    allocator.free(&mem, ptr1);
    allocator.printActiveBlocks(&mem);
    std::cout << "\n";

    allocator.free(&mem, static_cast<char*>(ptr1) - blockSize);
    allocator.printActiveBlocks(&mem);
    std::cout << "\n";

    allocator.free(&mem, static_cast<char*>(ptr1) - (blockSize * 2));
    allocator.printActiveBlocks(&mem);
    std::cout << "\n";

    void* ptr2 = allocator.allocate(&mem, 178);
    allocator.printActiveBlocks(&mem);
    std::cout << "\n";

    void* ptr3 = allocator.allocate(&mem, 78);
    allocator.printActiveBlocks(&mem);
    std::cout << "\n";


    return 0;
}
