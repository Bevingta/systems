#ifndef UTILS_H
#define UTILS_H

/* Constants for ASCII and bit manipulation */
#define ASCII_BITS 7
#define ASCII_MASK ((1 << ASCII_BITS) - 1)
#define COUNT_BITS 3
#define COUNT_MASK ((1 << COUNT_BITS) - 1)
#define COUNTS_MASK ((1 << (COUNT_BITS * CHARS_PER_INT)) - 1)
#define CHARS_PER_INT 3

/* Function declarations */
FILE* fopen_checked(const char* filename, const char* mode);

#endif
