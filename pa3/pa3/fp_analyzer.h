#ifndef FP_ANALYZER_H
#define FP_ANALYZER_H

#include <stdio.h>
#include <math.h>
#include <string.h>

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

void print_bits(UINT_TYPE value, int num_bits);
void print_components(Converter conv);
void print_normalized(Converter conv);
void print_denormalized(Converter conv);
void print_reconstitution(Converter conv);
void print_special_values();
FP_TYPE power_of_2(int exponent);

#endif
