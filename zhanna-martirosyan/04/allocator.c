#include <stddef.h>
#include <stdio.h>

#define MEMSIZE 65536  //размер буфера памяти

struct Block{
    size_t size; //размер блока
    int free; //флаг, который показывает свободен ли блок
    struct Block *next; //указатель на следующий блок
    size_t numAllocatedBlocks; //количество выделенных блоков
    size_t boundaries[]; //границы выделенных блоков (flexible array member)
};

struct Memory{
    char buffer[MEMSIZE]; //буфер памяти
    struct Block *start;  //начало списка блоков
};

void initMemory(struct Memory *mem) { //инициализация аллокатора памяти
    mem->start = (struct Block *)mem->buffer; //устанавливаем где находится начальный блок в памяти
    mem->start->size = MEMSIZE - sizeof(struct Block); //устанавливаем размер блока
    mem->start->free = 1; //1, потому что блок свободен
    mem->start->next = NULL; //указатель на следующий блок == null
    mem->start->numAllocatedBlocks = 0;
}

void *alloc(struct Memory *mem, size_t size) { //выделяем блок памяти(функция получает указатель на структуру и размер выделяемого блока)
    struct Block *current = mem->start; //итератор current, который указывает на начало буфера памяти
    while (current) { //цикл, для того, чтобы найти подходящий блок для выделения памяти
        if (current->free && current->size >= size) { //проверяем свободен ли текущий блок и хватит ли места в блоке на наш выделяемый блок
            if (current->size > size + sizeof(struct Block)) {
                //eсли блок слишком большой, добавляем новый блок для оставшейся памяти
                struct Block *newBlock = (struct Block *)((char *)current + size + sizeof(struct Block)); //выделяем новый блок для оставшейся памяти
                //инициализируем метаданные для нового блока
                newBlock->size = current->size - size - sizeof(struct Block);
                newBlock->free = 1;
                newBlock->next = current->next;

                //обновляем метаданные текущего блока, отмечаем, что он занят, и указатель на следующий блок ставим наш новый блок
                current->size = size;
                current->free = 0;
                current->next = newBlock;
            }
            else {
                current->free = 0; //если места хватило, то просто отмечаем, что наш блок занят
            }

            //обновляем информацию о границах в первом блоке
            current->numAllocatedBlocks++; //увеличиваем число блоков
            current->boundaries[current->numAllocatedBlocks - 1] = (size_t)current + sizeof(struct Block); //вычисляет адрес границы, добавляя к адресу начала блока размер самого блока (sizeof(struct Block))
            return (char *)current + sizeof(struct Block); //возвразаем на начало нашего нового выделенного блока
        }

        current = current->next; //переходим к следующему блоку
    }

    return NULL;  //возвращаем null, если не удалось выделить память
}

void free(struct Memory *mem, void *ptr) {
    struct Block *current = mem->start; //итератор current, который указывает на начало буфера памяти

    while (current) { //цикл, для того, чтобы найти наш блок для очистки
        if ((void *)current + sizeof(struct Block) == ptr) {
            //если указатель + размер блока == указатель на нужный блок, то отмечаем, что блок теперь свободен
            current->free = 1;
            return;
        }
        current = current->next; //переходим к следующему блоку
    }
}

void clean(struct Memory* mem)
{
    struct Block *current = mem->start; //итератор current, который указывает на начало буфера памяти

    while (current) {
        current->free = 1;
        current = current->next; //переходим к следующему блоку
    }
}

int main() {
    struct Memory mem; //создаем аллокатор памяти

    initMemory(&mem); //инициализируем его

    void *allocatedMemory = alloc(&mem, 100); //выделяем блок памяти в 100 байт. allocatedMemory возвращает
    // указатель на начало выделенного блока

    if (allocatedMemory != NULL) { //если этот указатель не равен нулю, то выделение памяти прошло успешно
        printf("Memory allocated at address: %p\n", allocatedMemory); //печатаем, что память успешно выделена и печатаем адрес

        free(&mem, allocatedMemory); //освобождаем этот блок памяти
        printf("Memory freed at address: %p\n", allocatedMemory); //печатаем, что память успешно очищена и печатаем адрес
    }
    else {
        printf("Failed to allocate memory.\n");
    }

    return 0;
}