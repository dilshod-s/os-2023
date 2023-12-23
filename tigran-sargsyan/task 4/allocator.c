#include <stdio.h>
#include <string.h>

#define MEMSIZE (2 << 16)
#define PGSIZE (2 << 8)

struct Memory {
    char buffer[MEMSIZE];
};

void initMem(struct Memory* mem) {
    memset(&mem->buffer, 0, MEMSIZE);
    mem->buffer[0] = 1;
}

int index2address(int idx) {
    return idx * PGSIZE;
}

int address2index(int addr) {
    return addr / PGSIZE;
}

void* alloc(struct Memory* mem, size_t sz) {
    if (sz > PGSIZE) {
        // Search for free space
        for (int i = 0; i < MEMSIZE; i += PGSIZE) {
            if (mem->buffer[i] == 0) {
                break;
            }
        }

        // Check if space is available
        if (i + PGSIZE > MEMSIZE) {
            return NULL;
        }

        // Mark space as allocated
        mem->buffer[i] = 1;

        // Return address
        return &mem->buffer[i];
    } else {
        // Search for free space
        int i = 1;
        for (; i < PGSIZE; i++) {
            if (mem->buffer[i] == 0) {
                break;
            }
        }

        // Mark space as allocated
        mem->buffer[i] = 1;

        // Return address
        int addr = index2address(i);
        return &mem->buffer[addr];
    }
}

int free(struct Memory* mem, void* ptr) {
    if ((size_t)ptr % PGSIZE != 0) {
        return -1;
    }

    int index = address2index((int)(ptr - (void*)mem->buffer));

    mem->buffer[index] = 0;
    return PGSIZE;
}

int clean(struct Memory* mem) {
    memset(&mem->buffer, 0, MEMSIZE);
    mem->buffer[0] = 1;
    return MEMSIZE;
}

int main() {
    struct Memory mem;
    initMem(&mem);

    void* ptr1 = alloc_1(&mem, 128);
    printf("Payload (alloc_1) // pointer = %lx\n", (size_t)ptr1);

    void* ptr2 = alloc(&mem, 256);
    printf("Payload (alloc) // pointer = %lx\n", (size_t)ptr2);

    free(&mem, ptr1);

    void* ptr3 = alloc(&mem, 64);
    printf("Payload (alloc) // pointer = %lx\n", (size_t)ptr3);

    clean(&mem);

    return 0;
}
