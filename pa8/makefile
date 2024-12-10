APP = matrix_mult
FLAGS = -Wall -Werror -std=gnu99

${APP}: ${APP}.c main.c
	gcc ${FLAGS} $^ -o $@ -pthread

clean:
	rm -f ${APP}
