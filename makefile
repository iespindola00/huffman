# Makefile para P3
FLAGS = -Wall -Wextra -Werror -std=c99

huff: main.o IO/io.o BTree/btree.o GList/glist.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c IO/io.h BTree/btree.h GList/glist.h
	$(CC) -c $< $(FLAGS)

IO/io.o: IO/io.c IO/io.h
	$(CC) -c $< $(FLAGS)

BTree/btree.o: BTree/btree.c BTree/btree.h
	$(CC) -c $< $(FLAGS)

GList/glist.o: GList/glist.c GList/glist.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm huff

.PHONY = clean
