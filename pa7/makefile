APP = mem_alloc
FLAGS = -Wall -Wextra -std=gnu99

all: $(APP)

$(APP): $(APP).c
	gcc $(FLAGS) $^ -o $@

test: $(APP).c test_main.c
	gcc $(FLAGS) $^ -o $@

clean:
	rm -f $(APP) test

