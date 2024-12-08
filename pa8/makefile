# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
LDFLAGS = -lm # Link math library if needed

# Source and object files
SRCS = main.c timing.c matrix.c
OBJS = $(SRCS:.c=.o)

# Output binary
TARGET = matrix_test

# Default rule to build the program
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile individual source files into objects
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything from scratch
rebuild: clean all

# Debug rule to check object files and program flow
debug: CFLAGS += -DDEBUG
debug: rebuild run
