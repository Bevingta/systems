#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H

#include <stddef.h> // For size_t
#include <sys/mman.h> // For mmap, munmap
#include <unistd.h> // For system constants like page size

// Symbolic Constants
#define PAGE_SIZE 4096
#define WORD_SIZE 8
#define SUCCESS 0
#define FAILURE -1

// Header Structure
typedef struct Header {
    size_t size; // Size of the block (payload + header), last bit for allocation flag
    struct Header *next; // Next block in the free list
    struct Header *previous; // Previous block in the free list
} Header;

// Global Free List
extern Header *free_list;

// Public API Functions
void *mem_alloc(size_t size);
void mem_free(void *ptr);

#endif // MEM_ALLOC_H


