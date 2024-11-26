#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096
#define WORD_SIZE 8
#define SUCCESS 0
#define FAILURE -1

typedef struct Header{
  size_t size;
  struct Header *next;
  struct Header *previous;
} Header;

extern Header * free_list;

void* mem_alloc(size_t size);
void mem_free(void* ptr);

Header* get_header(void* ptr);
void print_header(Header* header);
void print_list();
