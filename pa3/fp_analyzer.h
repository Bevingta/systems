#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef DOUBLE
#define FP_TYPE double
#define UINT_TYPE unsigned long
#define EXPONENT_BITS 11
#define MANTISSA_BITS 52
#define BIAS 1023
#define FORMAT_SPECIFIER "%.45lf"
#define SCANF_SPECIFIER "%lf"
#else
#define FP_TYPE float
#define UINT_TYPE unsigned int
#define EXPONENT_BITS 8
#define MANTISSA_BITS 23
#define BIAS 127
#define FORMAT_SPECIFIER "%.45f"
#define SCANF_SPECIFIER "%f"
#endif

#define SIGN_BITS 1
#define TOTAL_BITS (SIGN_BITS + EXPONENT_BITS + MANTISSA_BITS)

typedef struct {
    UINT_TYPE mantissa : MANTISSA_BITS;
    UINT_TYPE exponent : EXPONENT_BITS;
    UINT_TYPE sign : SIGN_BITS;
} Components;

typedef union {
    FP_TYPE f;
    UINT_TYPE i;
    Components c;
} Converter;

void print_special_values();
