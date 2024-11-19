#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


#define PAGE_SIZE 4096
#define WORD_SIZE 8
#define SUCCESS 0
#define FAILURE -1

typedef struct Header {
    size_t size;
    struct Header *next;
    struct Header *prev;
} Header;

Header *free_list = NULL;

