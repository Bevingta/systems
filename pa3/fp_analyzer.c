include "fp_analyzer.h"

void print_bits(UINT_TYPE value, int num_bits) {
    UINT_TYPE mask = ((UINT_TYPE)1 << (num_bits - 1));
    for (int i = 0; i < num_bits; i++) {
        putchar(value & mask ? '1' : '0');
        mask >>= 1;
    }
}

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
