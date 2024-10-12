#include "fp_analyzer.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "special") == 0) {
        print_special_values();
        return 0;
    }

    printf("Please enter a floating-point number or q to quit.\n");
    char input[256];
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0) {
            break;
        }
        Converter conv;
        if (sscanf(input, SCANF_SPECIFIER, &conv.f) == 1) {
            printf("%.6f\n", conv.f);
            print_components(conv);
            print_reconstitution(conv);
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
    return 0;
}
