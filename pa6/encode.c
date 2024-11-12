// Andrew Bevington / Gleidson De Sousa
// bevingta@bc.edu  / desousag@bc.edu

#include <stdio.h>
#include <stdlib.h>
#include "encode.h"

unsigned char ones(unsigned char input) {
    return 0;
}

unsigned char rotate(unsigned char plain, const unsigned char count) {
    return 0;
}

unsigned int encode_chars(const unsigned char * const plain_chars) {
    return 0;
}

void encode_file(const char * const input_file, const char * const output_file) {
    FILE * input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error: cannot open file %s\n", input_file);
        return;
    }
    FILE * output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Error: cannot open file %s\n", output_file);
        return;
    }
}

int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("Usage: ./encode <input file> <output file>\n");
        return 1;
    }

    encode_file(argv[1], argv[2]);
    return 0;
}
