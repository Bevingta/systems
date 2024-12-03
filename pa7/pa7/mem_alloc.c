// Andrew Bevington / Gleidson De Sousa
// bevingta@bc.edu  / desousag@bc.edu

#define _GNU_SOURCE
#include "mem_alloc.h"

Header *free_list = NULL;

int is_allocated(Header *header) { return header->size & 1; }

int is_free(Header *header) { return !(header->size & 1); }

void set_allocated(Header *header) { header->size |= 1; }

void set_free(Header *header) { header->size &= ~1; }

size_t get_size(Header *header) { return header->size & ~1; }

Header *get_header(void *ptr) {
  return (Header *)((char *)ptr - sizeof(Header));
}

int same_page(Header *h1, Header *h2) {
  return ((size_t)h1 & ~0xFFF) == ((size_t)h2 & ~0xFFF);
}

void print_header(Header *header) {
  printf("        Addr: %p\n", (void *)header);
  printf("        Size: %lu\n", get_size(header));
  printf("        Previous %p\n", (void *)header->previous);
  printf("        Next: %p\n", (void *)header->next);
}

void print_list() {
  Header *current = free_list;
  if (current == NULL) {
    printf("(Empty list.)");
  }

  while (current != NULL) {
    printf("%p -> ", (void *)current);
    current = current->next;
  }
  printf("\n");
}

int mem_init() {
  void *memory = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (memory == MAP_FAILED) {
    return FAILURE;
  }

  free_list = (Header *)memory;
  free_list->size = PAGE_SIZE - sizeof(Header);
  free_list->next = NULL;
  free_list->previous = NULL;
  set_free(free_list);
  return SUCCESS;
}

int mem_extend(Header *last) {
  void *new_page = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (new_page == MAP_FAILED) {
    return FAILURE;
  }

  Header *new_header = (Header *)new_page;
  new_header->size = PAGE_SIZE - sizeof(Header);
  new_header->next = NULL;
  new_header->previous = last;
  set_free(new_header);

  last->next = new_header;
  return SUCCESS;
}

void *mem_alloc(size_t requested_size) {
    if (requested_size > (PAGE_SIZE - sizeof(Header))) {
        return NULL;
    }

    if (free_list == NULL) {
        if (mem_init() == FAILURE) {
            return NULL;
        }
    }

    size_t aligned_size = (requested_size + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1);

    Header *current = free_list;
    while (current != NULL) {
        if (!is_allocated(current) && get_size(current) >= aligned_size) {
            if (get_size(current) >= aligned_size + sizeof(Header) + WORD_SIZE) {
                Header *new_header = 
                    (Header *)((char *)current + sizeof(Header) + aligned_size);
                new_header->size = get_size(current) - aligned_size - sizeof(Header);
                new_header->next = current->next;
                new_header->previous = current;
                set_free(new_header);

                current->size = aligned_size;
                current->next = new_header;

                if (new_header->next != NULL) {
                    new_header->next->previous = new_header;
                }
            }

            set_allocated(current);
            return (void *)((char *)current + sizeof(Header));
        }

        if (current->next == NULL) {
            if (mem_extend(current) == FAILURE) {
                return NULL;
            }
        }
        current = current->next;
    }

    return NULL;
}

void mem_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    Header *header = get_header(ptr);
    set_free(header);

    if (header->next != NULL && !is_allocated(header->next) &&
        same_page(header, header->next)) {
        Header *next = header->next;
        header->size = get_size(header) + sizeof(Header) + get_size(next);
        header->next = next->next;
        if (next->next != NULL) {
            next->next->previous = header;
        }
    }

    if (header->previous != NULL && !is_allocated(header->previous) &&
        same_page(header, header->previous)) {
        Header *prev = header->previous;
        prev->size = get_size(prev) + sizeof(Header) + get_size(header);
        prev->next = header->next;
        if (header->next != NULL) {
            header->next->previous = prev;
        }
        header = prev;
    }

    if (get_size(header) == PAGE_SIZE - sizeof(Header)) {
        Header *current = free_list;
        int total_pages = 0;
        while (current != NULL) {
            total_pages++;
            current = current->next;
        }

        if (total_pages == 1) {
            munmap(header, PAGE_SIZE);
            free_list = NULL;
            return;
        }

        if (header == free_list) {
            free_list = header->next;
            if (free_list != NULL) {
                free_list->previous = NULL;
            }
        } else {
            if (header->previous != NULL) {
                header->previous->next = header->next;
            }
            if (header->next != NULL) {
                header->next->previous = header->previous;
            }
        }
        munmap(header, PAGE_SIZE);
    }
}
