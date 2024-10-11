#include "fp_analyzer.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "special") == 0) {
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
        return 0;
    }

    printf("Please enter a floating-point number or q to quit.\n");
    char input[256];
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        // Remove trailing newline if present
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0) {
            break;
        }
        Converter conv;
        #ifdef DOUBLE
        if (sscanf(input, "%lf", &conv.f) == 1) {
            printf("%.6f\n", conv.f);
        #else
        if (sscanf(input, "%f", &conv.f) == 1) {
            printf("%.6f\n", conv.f);
        #endif
            print_components(conv);
            print_reconstitution(conv);
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
    return 0;
}
