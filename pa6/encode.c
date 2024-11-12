// Andrew Bevington / Gleidson De Sousa
// bevingta@bc.edu  / desousag@bc.edu

#include <stdio.h>
#include <stdlib.h>

//returns the number of set bits in input
unsigned char ones(unsigned char input) {
    //get the number of set bits in input
    unsigned char count = 0;
    while (input) {
        count += input & 1;
        input >>= 1;
    }
    return count;
}

// returns an encrypted version of plain,with the 7 bits rotated count positions to the left
unsigned char rotate(unsigned char plain, const unsigned char count) {
    //rotate the bits of plain count positions to the left
    return (plain << count) | (plain >> (7 - count));
}

// Returns a datum consisting of the encrypted encoding of three characters in the array chars
unsigned int encode_chars(const unsigned char * const plain_chars) {
    //get the encrypted encoding of three characters in the array chars
    unsigned int encoding = 0;
    for (int i = 0; i < 3; i++) {
        encoding = (encoding << 9) | (ones(plain_chars[i]) << 6) | rotate(plain_chars[i], 3);
    }
    return encoding;
}

// Opens input_file and output_file.  Reads ASCII characters from input_file and writes the encrypted encoding of the 
// text to output_file. Closes both
void encode_file(const char * const input_file, const char * const output_file) {
    FILE * input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error: cannot open file %s\n", input_file);
        return;
    }
    FILE * output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Error: cannot open file %s\n", output_file);
        return;
    }

    //read the input file and write the encrypted encoding of the text to the output file
    unsigned char plain_chars[3];
    while (fread(plain_chars, sizeof(unsigned char), 3, input) == 3) {
        unsigned int encoding = encode_chars(plain_chars);
        fwrite(&encoding, sizeof(unsigned int), 1, output);
    }

    fclose(input);
    fclose(output);
}

int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("Usage: ./encode <input file> <output file>\n");
        return 1;
    }

    encode_file(argv[1], argv[2]);
    return 0;
}
