#include <iostream>
#include <array>
#include <cstring>

constexpr std::size_t metaData = 12;
constexpr std::size_t blockSize = 256;
constexpr std::size_t blocksCount = 128;
constexpr std::size_t charArrSize = blockSize - metaData;

struct MemoryBlock {
    enum class State {
        Active, Passive
    } state;
    std::size_t bytesAllocated;
    char data[charArrSize];
};

struct Memory {
    std::array<MemoryBlock, blocksCount> blocks;
};

class DummyAllocator {
public:
    DummyAllocator() : allocatedMemory{nullptr} {
    }

    void *allocate(Memory *memory, std::size_t size) {
        std::cout << "memory to be allocated -> " << size << "\n";
        if (size == 0) { return nullptr; }

        std::size_t remainingSize = size;

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

    void initialize(Memory *memory) {
        for (auto &block: memory->blocks) {
            block.bytesAllocated = metaData;
            block.state = MemoryBlock::State::Passive;
            std::memset(block.data, 'a', charArrSize );
        }
    }

    int free(Memory *memory, void *ptr) {
        char *charPtr = static_cast<char *>(ptr);
        for (auto &block: memory->blocks) {
            char *blockStart = block.data + metaData;
            char *blockEnd = blockStart + charArrSize - metaData;
            if (charPtr >= blockStart && charPtr <= blockEnd) {
                block.state = MemoryBlock::State::Passive;
                block.bytesAllocated = 0;
                std::memset(blockStart, 0, charArrSize - metaData);
                return 0;
            }
        }
        return -1;
    }


    void clean(Memory *memory) {
        initialize(memory);
    }

    void printActiveBlocks(Memory *memory) {
        int count = 0;
        for (auto i = 0; i < memory->blocks.size(); ++i) {
            std::cout << "Metadata: 12 + clear bytes: " << memory->blocks[i].bytesAllocated - metaData << "\n ";
        }
    }

    ~DummyAllocator() = default;

private:
    void *allocatedMemory{};
};

int main() {
    Memory mem;
    DummyAllocator allocator;

    allocator.initialize(&mem);
    void *ptr1 = allocator.allocate(&mem, 1265);
    allocator.printActiveBlocks(&mem);

    return 0;
}