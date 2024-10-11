CC = gcc
FLAGS = -Wall -Werror -std=c99
APP = fp_analyzer

all: $(APP)_f $(APP)_d

$(APP)_f: fp_analyzer.c main.c
	$(CC) $(FLAGS) $^ -o $@ -lm

$(APP)_d: fp_analyzer.c main.c
	$(CC) $(FLAGS) -D DOUBLE $^ -o $@ -lm

clean:
	rm -f $(APP)_f $(APP)_d
