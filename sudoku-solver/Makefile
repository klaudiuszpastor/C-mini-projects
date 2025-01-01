TARGET = sudoku 
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
SRCS = sudoku.c puzzle.c
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

