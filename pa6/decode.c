#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Helper function to rotate bits right (opposite of encode's left rotation)
static unsigned char rotate_right(unsigned char encoded, unsigned char count) {
    // We only want to work with 7 bits (ASCII_BITS)
    encoded &= ASCII_MASK;
    // Perform right rotation
    return ((encoded >> count) | (encoded << (ASCII_BITS - count))) & ASCII_MASK;
}

void decode_chars(unsigned int input, unsigned char * const plain_chars) {
    // First, extract the three count values from the lowest 9 bits
    // Each count takes 3 bits
    unsigned char counts[3];
    counts[0] = input & COUNT_MASK;                    // Bits 0-2
    counts[1] = (input >> COUNT_BITS) & COUNT_MASK;    // Bits 3-5
    counts[2] = (input >> (2 * COUNT_BITS)) & COUNT_MASK; // Bits 6-8

    // Then extract the three encoded ASCII values
    // Each takes 7 bits, starting after the counts
    unsigned char encoded[3];
    encoded[0] = (input >> (3 * COUNT_BITS)) & ASCII_MASK;           // First 7-bit chunk
    encoded[1] = (input >> (3 * COUNT_BITS + ASCII_BITS)) & ASCII_MASK;    // Second 7-bit chunk
    encoded[2] = (input >> (3 * COUNT_BITS + 2 * ASCII_BITS)) & ASCII_MASK; // Third 7-bit chunk

    // Decode each character by rotating right by its count
    for (int i = 0; i < CHARS_PER_INT; i++) {
        plain_chars[i] = rotate_right(encoded[i], counts[i]);
    }
}

void decode_file(const char * const input_file, const char * const output_file) {
    FILE *in = fopen_checked(input_file, "rb");  // Open in binary read mode
    FILE *out = fopen_checked(output_file, "w"); // Open in text write mode
    
    unsigned int encoded_chunk;
    unsigned char decoded_chars[CHARS_PER_INT];
    
    // Read chunks of encoded data
    while (fread(&encoded_chunk, sizeof(unsigned int), 1, in) == 1) {
        // Decode the chunk into ASCII characters
        decode_chars(encoded_chunk, decoded_chars);
        
        // Write all three decoded characters
        // Note: Last chunk might contain padding zeros
        for (int i = 0; i < CHARS_PER_INT; i++) {
            if (decoded_chars[i] != 0) { // Only write non-null characters
                fputc(decoded_chars[i], out);
            }
        }
    }
    
    fclose(in);
    fclose(out);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input-ciphertext-file> <output-plaintext-file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    decode_file(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
