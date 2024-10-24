CC = gcc
FLAGS = -Wall -Werror -std=c99
APP = stats

$(APP): $(APP).c
	$(CC) $(FLAGS) $< -o $@ 

stats_mod: $(APP).s
	$(CC) $(APP).s -o stats_mod

clean:
	rm -f $(APP)
	rm -f stats_mod
