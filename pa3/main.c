#include "fp_analyzer.h"
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "special") == 0) {
        print_special_values();
        return 0;
    }

    printf("Please enter a floating-point number or q to quit.\n");
    while (1) {
        printf("> ");
        // Dynamic buffer allocation and input reading
        char* buffer = malloc(INITIAL_BUFFER_SIZE);
        if (!buffer) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        size_t buffer_size = INITIAL_BUFFER_SIZE;
        size_t input_length = 0;
        char* current_position = buffer;
        while (fgets(current_position, buffer_size - input_length, stdin) != NULL) {
            size_t line_length = strlen(current_position);
            input_length += line_length;
            if (current_position[line_length - 1] == '\n') {
                current_position[line_length - 1] = '\0';
                break;
            }
            buffer_size *= 2;
            char* new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer) {
                printf("Memory allocation failed.\n");
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
            current_position = buffer + input_length;
        }

        // Check for quit command before printing
        if (strcmp(buffer, "q") == 0 || strcmp(buffer, "Q") == 0) {
            free(buffer);
            break;
        }

        // Print the input with 6 decimal points
        Converter conv;
        if (sscanf(buffer, SCANF_SPECIFIER, &conv.f) == 1) {
            printf("%.6f\n", conv.f);
            print_components(conv);
            print_reconstitution(conv);
        } else {
            printf("%s\n", buffer);
            printf("Invalid input. Please try again.\n");
        }

        free(buffer);
    }
    return 0;
}
