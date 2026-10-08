#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5

void printNumbers(FILE *dst, int *numbers, int count, int capacity) {
    fprintf(dst, "(%d/%d) ", count, capacity);
    for (int index = 0; index < count; index++) {
        fprintf(dst, "%d ", numbers[index]);
    }
    fprintf(dst, "\n");
}

void addNumber(int *numbers, int *count, int numberToAdd) {
    numbers[(*count)++] = numberToAdd;
}

int main(void) {
    char *contentFilePath = "content.txt";
    FILE *contentFile;

    int numberCount = 0;
    // int numbers[CAPACITY] = {0};
    int capacity = CAPACITY;

    contentFile = fopen(contentFilePath, "r");
    if (contentFile == NULL) {
        fprintf(stderr, "Failed opening file '%s'\n", contentFilePath);
        return 1;
    }

    fscanf(contentFile, "(%d/%d) ", &numberCount, &capacity);

    int *numbers = malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Allocation failed\n");
        fclose(contentFile);
        return 1;
    }

    for (int numberIndex = 0; numberIndex < numberCount; numberIndex++) {
        fscanf(contentFile, "%d", &numbers[numberIndex]);
    }
    fclose(contentFile);

    addNumber(numbers, &numberCount, 10);

    printNumbers(stdout, numbers, numberCount, capacity);

    contentFile = fopen(contentFilePath, "w");
    if (contentFile == NULL) {
        fprintf(stderr, "Failed opening file '%s'\n", contentFilePath);
        return 1;
    }
    printNumbers(contentFile, numbers, numberCount, capacity);

    free(numbers);
    fclose(contentFile);
    return 0;
}
