#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5

void printNumbers(int *numbers, int count) {
    printf("(%d/%d) ", count, CAPACITY);
    for (int index = 0; index < count; index++) {
        printf("%d ", numbers[index]);
    }
    printf("\n");
}

void addNumber(int *numbers, int *count, int numberToAdd) {
    numbers[(*count)++] = numberToAdd;
}

int main(void) {
    int numberCount = 0;
    // int numbers[CAPACITY] = {0};
    int *numbers = malloc(CAPACITY * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }

    printf("sizeof(numbers) = %lu\n", sizeof(numbers));

    addNumber(numbers, &numberCount, 10);
    addNumber(numbers, &numberCount, 99);
    addNumber(numbers, &numberCount, 10);

    printNumbers(numbers, numberCount);

    free(numbers);
    return 0;
}
