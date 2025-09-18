
all: main

CC = clang
CFLAGS = -std=c11 -Werror -Wall -Wextra -pedantic

.PHONY: all run clean

main: main.c
	$(CC) $(CFLAGS) $^ -o "$@"

run: main
	./main

clean:
	rm main
