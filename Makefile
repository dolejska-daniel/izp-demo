CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic

.PHONY: clean pack run

main: main.c
	$(CC) $(CFLAGS) $^ -o "$@"

main-debug: main.c
	$(CC) $(CFLAGS) -DDEBUG_PRINT=1 $^ -o "$@"

btree: btree.c
	$(CC) $(CFLAGS) $^ -o "$@"

clean:
	rm -Rf *.o main btree odevzdani.tar.gz

pack:
	tar -czvf odevzdani.tar.gz ./*

run: main
	./main
