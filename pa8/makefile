CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = main.c functions.c
OUT = program

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
