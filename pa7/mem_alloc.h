#include <stdlib.h>
#include <stdio.h>

#define PAGS_SIZE 4096
#define WORD_SIZE 8
#define SUCCESS 0
#define FAILURE -1

typedef struct Header{
  size_t size;
  struct Header *next;
  struct Header *previous;
} Header;
