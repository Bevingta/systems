#include <stdio.h>
#include <stdlib.h>

#define TOTAL_BITS (sizeof(unsigned int) * 8) // Total bits in an unsigned int
#define FLOAT_SIZE (sizeof(float)) // Size of float in bytes
#define MAX_FLOAT_INPUT (1.0e10f) // Max float value for input

// Union to convert float to unsigned int
typedef union {
    float f;
    unsigned int i;
} Converter;

// Function to print bits of an unsigned int
void print_bits(unsigned int value) {
    unsigned int mask = 1 << (TOTAL_BITS - 1); // Create a mask with the leftmost bit set
    for (int i = 0; i < TOTAL_BITS; i++) {
        putchar(value & mask ? '1' : '0'); // Print '1' or '0' based on the mask
        mask >>= 1; // Shift mask to the right
    }
    putchar('\n'); // New line after printing bits
}

int main() {
    Converter conv; // Declare a union instance for conversion
    float input; // Variable to store user input

    printf("Please enter a floating-point number or q to quit.\n");
    while (1) {
        printf("Input: ");
        if (scanf("%f", &input) != 1) { // Read a float value
            // Check for termination condition
            char term[10];
            scanf("%s", term);
            if (term[0] == 'q') {
                break; // Exit the loop if user types 'exit'
            } else {
                printf("Invalid input. Please enter a float value.\n");
                continue; // Continue if invalid input
            }
        }
        
        conv.f = input; // Store the input float in the union
        printf("Bits of %f: ", conv.f);
        print_bits(conv.i); // Print the bits using the unsigned int representation
    }

    printf("Exiting program.\n");
    return 0; // Successful completion
}

