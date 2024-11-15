// Andrew Bevington / Gleidson De Sousa
// bevingta@bc.edu  / desousag@bc.edu

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* Returns the number of set bits in input */
unsigned char ones(unsigned char input) {
    unsigned char count = 0;
    for (int i = 0; i < ASCII_BITS; i++) {
        if (input & (1 << i)) {
            count++;
        }
    }
    return count;
}

/* Rotates the 7 bits of plain left by count positions */
unsigned char rotate(unsigned char plain, const unsigned char count) {
    plain &= ASCII_MASK;  // Ensure we only use 7 bits
    unsigned char rotated = 0;
    
    // Perform the rotation using modular arithmetic
    for (int i = 0; i < ASCII_BITS; i++) {
        int new_pos = (i + count) % ASCII_BITS;
        if (plain & (1 << i)) {
            rotated |= (1 << new_pos);
        }
    }
    
    return rotated;
}

/* Encodes three characters into a single unsigned int */
unsigned int encode_chars(const unsigned char* const plain_chars) {
    unsigned int result = 0;
    unsigned int counts = 0;
    unsigned int rotated_chars = 0;
    
    // Process each character
    for (int i = 0; i < CHARS_PER_INT; i++) {
        if (plain_chars[i]) {  // If character exists
            unsigned char count = ones(plain_chars[i]);
            unsigned char rotated = rotate(plain_chars[i], count);
            
            // Store count in the lower bits
            counts |= (count << (i * COUNT_BITS));
            
            // Store rotated character in upper portion
            rotated_chars |= ((unsigned int)rotated << (i * ASCII_BITS));
        }
    }
    
    // Combine the counts and rotated characters
    result = counts | (rotated_chars << (CHARS_PER_INT * COUNT_BITS));
    
    return result;
}

/* Processes input file and writes encoded output */
void encode_file(const char* const input_file, const char* const output_file) {
    FILE* in = fopen_checked(input_file, "r");
    FILE* out = fopen_checked(output_file, "wb");
   
    unsigned char buffer[CHARS_PER_INT];
    int chars_read;
    
    while (1) {
        // Clear buffer
        for (int i = 0; i < CHARS_PER_INT; i++) {
            buffer[i] = 0;
        }
        
        // Read up to CHARS_PER_INT characters
        chars_read = 0;
        for (int i = 0; i < CHARS_PER_INT; i++) {
            int c = fgetc(in);
            if (c == EOF) {
                break;
            }
            buffer[i] = (unsigned char)c;
            chars_read++;
        }
        
        if (chars_read == 0) {
            break;  // No more input
        }
        
        // Encode and write
        unsigned int encoded = encode_chars(buffer);
        fwrite(&encoded, sizeof(encoded), 1, out);
        
        if (chars_read < CHARS_PER_INT) {
            break;  // Partial group was the last one
        }
    }
    
    fclose(in);
    fclose(out);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input-plaintext-file> <output-ciphertext-file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    encode_file(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
