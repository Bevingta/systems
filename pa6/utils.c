#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

FILE* fopen_checked(const char* filename, const char* mode) {
    FILE* fp = fopen(filename, mode);
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }
    return fp;
}
