#include "fp_analyzer.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "special") == 0) {
        print_special_values();
        return 0;
    }
    
    printf("Please enter a floating-point number or q to quit.\n> ");

    float input;

    while (scanf("%f", &input)) {
        printf("The number you entered is %.45f\n", input);
        printf("> ");
    }
    return EXIT_SUCCESS;
}
