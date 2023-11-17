#include <iostream>

#define PageSize 256
// each pagte size
#define PageCount 256
// page_amount

struct Page {
  char data[PageSize];
};
struct Meta {
  bool is_valid = false;
  bool is_first = false;
};
struct Memory {
  Meta meta[256];
  Page pages[PageCount];
};
struct MemoryAllocation {
  MemoryAllocation() {}
  char *allocate(Memory *mem, size_t size) {
    if (!mem || size == 0) {
      return NULL;
    }
    int the_first_page = -1;
    size_t page_amount = size / PageSize;
    size_t count = 0;
    if (size % PageSize != 0) {
      page_amount++;
    }
    for (int i = 0; i < PageCount; i++) {
      if (mem->meta[i].is_valid == false)
        count++;
      else if (mem->meta[i].is_valid == true)
        count = 0;
      if (count == page_amount) {
        the_first_page = i - count + 1;
        break;
      }
      if (i == PageCount - 1) {
        return NULL;
      }
    }
    if (the_first_page == -1) {
      return NULL;
    }
    for (size_t j = the_first_page; j < the_first_page + count; j++) {
      if (j == the_first_page)
        mem->meta[j].is_first = true;
      mem->meta[j].is_valid = true;
    }
    return mem->pages[the_first_page].data;
  }
  void clear(Memory *mem) {
    if (!mem) {
      return;
    }
    for (int i = 0; i < PageCount; i++) {
      mem->meta[i].is_valid = false;
      mem->meta[i].is_first = false;
    }
    return;
  }
  size_t free(Memory *mem, void *ptr) {
    if (!mem || !ptr)
      return 0;
    size_t the_page = (uintptr_t)ptr - (uintptr_t)mem->pages;
    the_page /= PageSize;

    if (mem->meta[the_page].is_first == true) {
      mem->meta[the_page].is_first = false;
    }
    while (mem->meta[the_page].is_valid == true &&
           mem->meta[the_page].is_first == false) {
      mem->meta[the_page].is_valid = false;
      the_page++;
    }
    return the_page;
  }
};

int main() { std::cout << "Hello World!\n"; }
