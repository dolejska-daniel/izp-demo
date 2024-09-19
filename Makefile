
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic

.PHONY: clean

main: main.c
	$(CC) $(CFLAGS) $^ -o "$@"

clean:
	rm -Rf *.o main odevzdani.tar.gz

pack:
	tar -czvf odevzdani.tar.gz ./*
