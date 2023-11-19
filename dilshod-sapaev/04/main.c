#include <stdio.h>
#include <string.h>

#define MEMSIZE 2 << 16
#define PGSIZE 2 << 8

struct Memory {
	char buffer[MEMSIZE];
};

void initMem(struct Memory *mem) {
	memset(&mem->buffer, 0, MEMSIZE);
	// fist block is allocated for block index
	mem->buffer[0] = 1;
}

int index2address(int idx) {
	return idx * PGSIZE;
}

int address2index(int addr) {
	return addr / PGSIZE;
}

// Allocate max 1 page of memory
void *alloc_1(struct Memory *mem, size_t sz) {
	if (sz > PGSIZE) {
		// exit(1); // unimplemented
		return NULL;
	}

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
};

int free_1(struct Memory *mem, void *ptr) {
	if ((size_t) ptr % PGSIZE != 0) {
		return -1;
	}

	int index = address2index(
		(int) (ptr - (void *) mem->buffer)
	);

	mem->buffer[index] = 0;
	return 0;
}

int main() {

	struct Memory mem;
	memset(&mem.buffer, 0, MEMSIZE);

	void *ptr = &mem.buffer;
	printf("Payload // pointer = %lx\n",(size_t)mem.buffer);

	ptr = alloc_1(&mem, 128);
	printf("Payload // pointer = %lx\n", (size_t) ptr);

        ptr = alloc_1(&mem, 256);
	printf("Payload // pointer = %lx\n", (size_t) ptr);

	ptr = alloc_1(&mem, 1);
	printf("Payload // pointer = %lx\n", (size_t) ptr);

	return 0;
}

