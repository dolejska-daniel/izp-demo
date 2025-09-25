#include <stdio.h>

#define ARRAY_CAPACITY 10

void print_contents(int items[ARRAY_CAPACITY], int count) {
    if (count == 0) {
        printf("Items are empty.\n");
    }
    for (int index = 0; index < count; index++) {
        printf("item[%d] = %d\n", index, items[index]);
    }
}

int main(void) {
    int numbers[ARRAY_CAPACITY] = {0};
    int numbersCount = 0;

    print_contents(numbers, numbersCount);

    numbers[numbersCount++] = 10;
    numbers[numbersCount++] = 30;
    numbers[numbersCount++] = 50;

    print_contents(numbers, numbersCount);

    numbersCount--;
    print_contents(numbers, numbersCount);

    return 0;
}
