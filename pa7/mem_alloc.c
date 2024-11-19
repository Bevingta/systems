#include "mem_alloc.h"

Header * free_list = NULL;

int main() {
  printf("Size of Header: %lu\n", sizeof(Header));
  return 0;
}
