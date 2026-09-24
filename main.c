#include <stdio.h>

#define CAPACITY 5

void printNumbers(int numbers[CAPACITY], int count) {
    printf("(%d/%d) ", count, CAPACITY);
    for (int index = 0; index < count; index++) {
        printf("%d ", numbers[index]);
    }
    printf("\n");
}

int main(void) {
    int numberCount = 0;
    int numbers[CAPACITY] = {0};

    numbers[++numberCount] = 99;
    numbers[numberCount++] = 10;
    numberCount--;

    printNumbers(numbers, numberCount);

    return 0;
}
