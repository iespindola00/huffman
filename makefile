# Makefile para P3
FLAGS = -Wall -Wextra -Werror -std=c99

huff: main.o IO/io.o BTree/btree.o BTList/btlist.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c IO/io.h BTree/btree.h BTList/btlist.h
	$(CC) -c $< $(FLAGS)

IO/io.o: IO/io.c IO/io.h
	$(CC) -c $< $(FLAGS)

BTree/btree.o: BTree/btree.c BTree/btree.h
	$(CC) -c $< $(FLAGS)

BTList/btlist.o: BTList/btlist.c BTList/btlist.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm huff

.PHONY = clean
