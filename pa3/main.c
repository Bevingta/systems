#include "fp_analyzer.h"

int main(int argc, char **argv) {
  printf("Please enter a floating-point number or q to quit.\n> ");

  float input;

  while (scanf("%f", &input)) {
    printf("The number you entered is %.45f\n", input);
    printf("> ");
  }
  test_print();
  return EXIT_SUCCESS;
}
