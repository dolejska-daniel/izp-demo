
all: main main-mul2 main-pwr2

CC = clang
CFLAGS = -std=c11 -Werror -Wall -Wextra -pedantic

.PHONY: all run clean

keyfilter: keyfilter.c
	gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter

main: main.c libinc1.so
	$(CC) $(CFLAGS) $^ -o "$@"

libmul2.so: processing_mul2.c
	$(CC) $(CFLAGS) $^ -shared -o "$@"

libpwr2.so: processing_pwr2.c
	$(CC) $(CFLAGS) $^ -shared -o "$@"

libinc1.so: processing_inc1.c
	$(CC) $(CFLAGS) $^ -shared -o "$@"

main-debug: main.c
	$(CC) $(CFLAGS) $^ -DDEBUG_PRINT -g -o "$@"

run: main
	./main

clean:
	rm main
