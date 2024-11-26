APP = mem_alloc
FLAGS = -Wall -Werror -std=c99

main: main.c $(APP).c
	gcc $(FLAGS) $^ -o $@

test: $(APP).c test_main.c
	gcc $(FLAGS) $^ -o $@

clean:
	rm -f main test *.o
