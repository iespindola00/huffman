FLAGS = -Wall -Wextra -Werror -std=c99 -Os
CC = gcc

huff: main.o io.o btree.o btlist.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c IO/io.h BTree/btree.h BTList/btlist.h
	$(CC) -c $< $(FLAGS)

io.o: IO/io.c IO/io.h
	$(CC) -c $< $(FLAGS)

btree.o: BTree/btree.c BTree/btree.h
	$(CC) -c $< $(FLAGS)

btlist.o: BTList/btlist.c BTList/btlist.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm *.tree
	rm *.hf
	rm huff
.PHONY = clean
