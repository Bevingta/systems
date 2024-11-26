#include "mem_alloc.h"
#include <stdio.h> // For debugging
#include <string.h> // For memset

Header *free_list = NULL;

// Helper Functions
static inline int is_allocated(Header *header) {
    return header->size & 1;
}

static inline void set_allocated(Header *header) {
    header->size |= 1;
}

static inline void set_free(Header *header) {
    header->size &= ~1;
}

static inline size_t get_size(Header *header) {
    return header->size & ~1;
}

static inline Header *get_header(void *mem) {
    return (Header *)((char *)mem - sizeof(Header));
}

static inline int same_page(Header *h1, Header *h2) {
    return (((size_t)h1) & ~(PAGE_SIZE - 1)) == (((size_t)h2) & ~(PAGE_SIZE - 1));
}

// Initialize the memory allocator
int mem_init() {
    void *block = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED) {
        return FAILURE;
    }
    free_list = (Header *)block;
    free_list->size = PAGE_SIZE - sizeof(Header);
    free_list->next = NULL;
    free_list->previous = NULL;
    return SUCCESS;
}

// Extend the free list
int mem_extend(Header *last) {
    void *block = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED) {
        return FAILURE;
    }
    Header *new_header = (Header *)block;
    new_header->size = PAGE_SIZE - sizeof(Header);
    new_header->next = NULL;
    new_header->previous = last;
    last->next = new_header;
    return SUCCESS;
}

// Allocate memory
void *mem_alloc(size_t requested_size) {
    if (requested_size > PAGE_SIZE - sizeof(Header)) {
        return NULL;
    }
    if (!free_list && mem_init() == FAILURE) {
        return NULL;
    }

    size_t aligned_size = (requested_size + WORD_SIZE - 1) & ~(WORD_SIZE - 1);
    Header *current = free_list;

    while (current) {
        if (is_allocated(current) || get_size(current) < aligned_size) {
            current = current->next;
            continue;
        }

        if (get_size(current) > aligned_size + sizeof(Header)) {
            Header *new_block = (Header *)((char *)current + sizeof(Header) + aligned_size);
            new_block->size = get_size(current) - aligned_size - sizeof(Header);
            new_block->next = current->next;
            new_block->previous = current;
            if (current->next) {
                current->next->previous = new_block;
            }
            current->next = new_block;
            current->size = aligned_size;
        }
        set_allocated(current);
        return (char *)current + sizeof(Header);
    }

    if (mem_extend(current) == SUCCESS) {
        return mem_alloc(requested_size);
    }
    return NULL;
}

// Free allocated memory
void mem_free(void *ptr) {
    if (!ptr) return;

    Header *header = get_header(ptr);
    set_free(header);

    // Coalesce with next block
    if (header->next && !is_allocated(header->next) && same_page(header, header->next)) {
        header->size += sizeof(Header) + get_size(header->next);
        header->next = header->next->next;
        if (header->next) {
            header->next->previous = header;
        }
    }

    // Coalesce with previous block
    if (header->previous && !is_allocated(header->previous) && same_page(header, header->previous)) {
        header->previous->size += sizeof(Header) + get_size(header);
        header->previous->next = header->next;
        if (header->next) {
            header->next->previous = header->previous;
        }
    }

    // Unmap if a whole page is free
    if (get_size(header) == PAGE_SIZE - sizeof(Header)) {
        if (header->previous) {
            header->previous->next = header->next;
        }
        if (header->next) {
            header->next->previous = header->previous;
        }
        if (header == free_list) {
            free_list = header->next;
        }
        munmap(header, PAGE_SIZE);
    }
}

// Debugging Functions
void print_header(Header *header) {
    printf("Header %p | Size: %zu | Allocated: %d | Next: %p | Prev: %p\n",
           (void *)header, get_size(header), is_allocated(header), (void *)header->next, (void *)header->previous);
}

void print_list() {
    Header *current = free_list;
    while (current) {
        print_header(current);
        current = current->next;
    }
}


