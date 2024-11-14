CC = gcc
CFLAGS = -Wall -Werror -std=c99

all: encode decode

encode: encode.c utils.c utils.h
	$(CC) $(CFLAGS) encode.c utils.c -o encode

decode: decode.c utils.c utils.h
	$(CC) $(CFLAGS) decode.c utils.c -o decode

clean:
	rm -f encode decode
