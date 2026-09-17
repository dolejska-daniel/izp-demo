
CC = clang
CFLAGS =  -std=c11 -Wall -Wextra -pedantic -Werror
MAIN_DEPS = main.c

main: $(MAIN_DEPS)
	$(CC) $(CFLAGS) $^ -o $@

main.c: main__.c
	cp main__.c main.c

clean:
	rm main
