#include <stdio.h>
#include <string.h>

#define MEMSIZE 2 << 16
#define PGSIZE 2 << 8

struct Memory {
	char buffer[MEMSIZE];
};

void initMem(struct Memory *mem) {
	memset(&mem->buffer, 0, MEMSIZE);
	// Выделяем первый блок для индекса блока
	mem->buffer[0] = 1;
}

int index2address(int idx) {
	return idx * PGSIZE;
}

int address2index(int addr) {
	return addr / PGSIZE;
}

// Выделяем максимум 1 страницу памяти
void *alloc_1(struct Memory *mem, size_t sz) {
	if (sz > PGSIZE) {
		return NULL;
	}

	// Поиск свободного места
	for (int i = 1; i < PGSIZE; i++) {
		if (mem->buffer[i] == 0) {
			break;
		}
	}

	// Отмечаем пространство как выделенное
	mem->buffer[i] = 1;

	// Возвращаем адрес
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

	ptr = alloc_1(&mem, 100);
	printf("Payload // pointer = %lx\n",(size_t)ptr);

	free_1(&mem, ptr);

	return 0;
}
