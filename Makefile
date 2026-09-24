
CC = clang
CFLAGS =  -std=c11 -Wall -Wextra -pedantic -Werror
MAIN_DEPS = main.c

main: $(MAIN_DEPS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm main
