#include <cstddef>

// Структура для хранения информации о блоках памяти
struct Block {
    size_t size;      // размер блока памяти
    bool free;        // флаг, указывающий, свободен ли блок
    struct Block* next; // указатель на следующий блок
};

// Структура для хранения информации о выделенной памяти
struct Memory {
    struct Block* head; // указатель на начало списка блоков
};

// Инициализация аллокатора
void initAllocator(Memory* mem, size_t size) {
    // Выделяем память для аллокатора
    mem->head = reinterpret_cast<Block*>(new char[size]);
    mem->head->size = size - sizeof(Block);
    mem->head->free = true;
    mem->head->next = nullptr;
}

// Выделение блока памяти
void* alloc(Memory* mem, size_t size) {
    // Поиск свободного блока в списке
    Block* current = mem->head;
    while (current != nullptr) {
        if (current->free && current->size >= size) {
            // Найден подходящий свободный блок
            current->free = false; // блок теперь занят
            return reinterpret_cast<void*>(current + 1); // возвращаем указатель на данные (после заголовка блока)
        }
        current = current->next;
    }

    // Если свободный блок не найден, вернуть NULL
    return nullptr;
}

// Освобождение блока памяти
int my_free(Memory* mem, void* ptr) {
    if (ptr == nullptr) {
        return 0;
    }

    // Получаем указатель на заголовок блока
    Block* block = reinterpret_cast<Block*>(ptr) - 1;

    // Помечаем блок как свободный
    block->free = true;

    return static_cast<int>(block->size);
}

// Освобождение памяти, выделенной аллокатором
void destroyAllocator(Memory* mem) {
    delete[] reinterpret_cast<char*>(mem->head);
}

// Пример использования аллокатора
int main() {
    Memory myAllocator;
    initAllocator(&myAllocator, 1024);

    // Выделение памяти
    int* arr = static_cast<int*>(alloc(&myAllocator, 5 * sizeof(int)));

    // Использование выделенной памяти
    for (int i = 0; i < 5; ++i) {
        arr[i] = i;
    }

    // Освобождение памяти
    int freedBytes = my_free(&myAllocator, arr);

    // Уничтожение аллокатора
    destroyAllocator(&myAllocator);

    return 0;
}
