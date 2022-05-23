# Makefile para P3
FLAGS = -Wall -Wextra -Werror -std=c99

huff: main.o io.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c io.h
	$(CC) -c $< $(FLAGS)

io.o: io.c io.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm huff

.PHONY = clean
