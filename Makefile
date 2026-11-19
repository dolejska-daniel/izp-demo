
CC = clang
CFLAGS =  -std=c11 -Wall -Wextra -pedantic -Werror
MAIN_DEPS = main.c

main: $(MAIN_DEPS)
	$(CC) $(CFLAGS) $^ -o $@

main-debug: $(MAIN_DEPS)
	$(CC) $(CFLAGS) -DDEBUG $^ -o $@

libs: numbers_mul.so numbers_sub.so

numbers_mul.so: numbers_mul.o
	$(CC) $(CFLAGS) -shared $^ -o numbers_mul.so

numbers_mul.o: numbers_mul.c
	$(CC) $(CFLAGS) -fPIC -c $^

numbers_sub.so: numbers_sub.o
	$(CC) $(CFLAGS) -shared $^ -o numbers_sub.so

numbers_sub.o: numbers_sub.c
	$(CC) $(CFLAGS) -fPIC -c $^

factorial: factorial.c
	$(CC) $(CFLAGS) $^ -o $@

run-factorial: factorial
	./factorial

run: main
	./main

clean:
	rm main
