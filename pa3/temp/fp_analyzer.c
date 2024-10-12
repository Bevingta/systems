#include "fp_analyzer.h"

// prints the bits with the mask we used in class
void print_bits(UINT_TYPE value, int num_bits) {
    // mask is 1000...0000
    UINT_TYPE mask = ((UINT_TYPE)1 << (num_bits - 1));
    // loops through every position in the mask
    for (int i = 0; i < num_bits; i++) {
        // essentially checks every bit in the value
        putchar(value & mask ? '1' : '0');
        mask >>= 1;
    }
}

// automatically prints the sign, exponent, and mantissa (based on in class work)
void print_components(Converter conv) {
    printf("All bits: ");
    print_bits(conv.i, TOTAL_BITS);
    printf("\nSign: %u\n", conv.c.sign);
    printf("Exponent: ");
    print_bits(conv.c.exponent, EXPONENT_BITS);
    printf("\nMantissa: ");
    print_bits(conv.c.mantissa, MANTISSA_BITS);
    printf("\n");
}

// custom 2^x function
FP_TYPE power_of_2(int exponent) {
    FP_TYPE result = 1.0;
    // if the exponent is positive, multiply by 2 that many times
    if (exponent >= 0) {
        for (int i = 0; i < exponent; i++) {
            result *= 2.0;
        }
    // if the exponent is negative, divide by 2 that many times
    } else {
        for (int i = 0; i < -exponent; i++) {
            result /= 2.0;
        }
    }
    return result;
}

// prints the normalized value
void print_normalized(Converter conv) {
    // true exponent is the exponent - the bias
    int true_exponent = conv.c.exponent - BIAS;
    // mantissa value is 0 initially
    FP_TYPE mantissa_value = 0.0;
    // loops through the mantissa bits
    for (int i = MANTISSA_BITS - 1; i >= 0; i--) {
        // if the bit is 1, add 2^(-i) to the mantissa value
        if (conv.c.mantissa & ((UINT_TYPE)1 << i)) {
            mantissa_value += power_of_2(-(MANTISSA_BITS - i));
        }
    }
    
    // printing the equation
    printf("(-1)^{%u} x (1 + %.6f) x 2^{%d - %d}\n", conv.c.sign, mantissa_value, conv.c.exponent, BIAS);
    printf("  = %s1 x %.6f x 2^{%d}\n", conv.c.sign ? "-" : "", 1.0 + mantissa_value, true_exponent);
    printf("  = %s1 x %.6f x %.0f\n", conv.c.sign ? "-" : "", 1.0 + mantissa_value, power_of_2(true_exponent));
    printf("  = ");
    printf(FORMAT_SPECIFIER, conv.f);
    printf("\n");
}

// prints the denormalized value
void print_denormalized(Converter conv) {
    // handling special
    if (conv.i == 0 || conv.i == (UINT_TYPE)1 << (TOTAL_BITS - 1)) {
        printf("Original value: %s0.0\n", conv.c.sign ? "-" : "");
    // increasing the mantissa to be the correct value
    } else {
        FP_TYPE mantissa_value = 0.0;
        for (int i = MANTISSA_BITS - 1; i >= 0; i--) {
            if (conv.c.mantissa & ((UINT_TYPE)1 << i)) {
                mantissa_value += power_of_2(-(MANTISSA_BITS - i));
            }
        }
        
        printf("(-1)^{%u} x " FORMAT_SPECIFIER " x 2^{1 - %d}\n", conv.c.sign, mantissa_value, BIAS);
        printf("  = %s1 x %.6f x 2^{%d}\n", conv.c.sign ? "-" : "", mantissa_value, 1 - BIAS);
        printf("  = %s %.6f x 1/", conv.c.sign ? "-1 x" : "", mantissa_value);
        printf("%.0f\n", power_of_2(BIAS - 1));
        printf("  = ");
        printf(FORMAT_SPECIFIER, conv.f);
        printf("\n");
    }
}

void print_reconstitution(Converter conv) {
    printf("Original value:\n");
    if (conv.c.exponent == 0) {
        print_denormalized(conv);
    } else if (conv.c.exponent == ((1 << EXPONENT_BITS) - 1)) {
        if (conv.c.mantissa == 0) {
            printf("%sinf\n", conv.c.sign ? "-" : "");
        } else {
            printf("%snan\n", conv.c.sign ? "-" : "");
        }
    } else {
        print_normalized(conv);
    }
}

void print_special_values() {
    FP_TYPE special_values[] = {INFINITY, -INFINITY, NAN, -NAN};
    for (int i = 0; i < 4; i++) {
        Converter conv;
        conv.f = special_values[i];
        if (isnan(conv.f)) {
            printf("%snan\n", signbit(conv.f) ? "-" : "");
        } else {
            printf("%s\n", conv.f == INFINITY ? "inf" : "-inf");
        }
        print_components(conv);
        printf("\n");
    }
}
