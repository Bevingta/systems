#include <stdio.h>
#include <stdlib.h>

#define ASCII_BITS 7

void decode_file(const char *const input_file, const char *const output_file) {
  FILE *open = fopen(input_file, "r");
  FILE *output = fopen(output_file, "w");

  if (open == NULL || output == NULL) {
    if (open)
      fclose(open);
    if (output)
      fclose(output);
    printf("Error: Unable to open file\n");
    exit(1);
  }

  int ch;
  while ((ch = fgetc(open)) != EOF) {
    unsigned char decrypted = decode_chars
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    return 1; // Exit with error code
  }

  decode_file(argv[1], argv[2]);
  return 0; // Successful execution
}
