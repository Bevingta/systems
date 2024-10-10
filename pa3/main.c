#include "fp_analyzer.h"
#include <string.h>

int main(int argc, char *argv[]) {
    // if the user wants to see the special values, print them and exit
    if (argc > 1 && strcmp(argv[1], "special") == 0) {
        print_special_values();
        return 0;
    }

    // printing the initial prompt
    printf("Please enter a floating-point number or q to quit.\n");
    char input[256];
    // loops until the user quits
    while (1) {
        printf("> ");
        // ways to quit
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        if (input[0] == 'q' || input[0] == 'Q') {
            break;
        }

        // initializing the converter
        Converter conv;

        #ifdef DOUBLE
        if (sscanf(input, "%lf", &conv.f) == 1) {
        #else
        if (sscanf(input, "%f", &conv.f) == 1) {
        #endif
            print_components(conv);
            print_reconstitution(conv);
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
    return 0;
}
