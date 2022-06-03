FLAGS = -Wall -Wextra -Werror -std=c99 -Os
CC = gcc

huff: main.o compresion.o decompresion.o io.o btree.o btlist.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c compresion.h decompresion.h IO/io.h BTree/btree.h BTList/btlist.h
	$(CC) -c $< $(FLAGS)

compresion.o: compresion.c compresion.h
	$(CC) -c $< $(FLAGS)

decompresion.o: decompresion.c decompresion.h
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
	rm *.txt.dec
	rm huff
.PHONY = clean
