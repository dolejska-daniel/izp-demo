#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define debug_printf(format, ...)                                                                                      \
    fprintf(stderr, "%s:%d | %s | " format "\n", __FILE__, __LINE__, __func__, __VA_ARGS__)

#define debug_print(format) fprintf(stderr, "%s\n", format)
#else
#define debug_printf(...)                                                                                              \
    while (0) {                                                                                                        \
    }
#define debug_print(x)                                                                                                 \
    while (0) {                                                                                                        \
    }
#endif

#define CAPACITY 5

void printNumbers(FILE *dst, int *numbers, int count, int capacity) {
    debug_print("printing contents");
    fprintf(dst, "(%d/%d) ", count, capacity);
    for (int index = 0; index < count; index++) {
        fprintf(dst, "%d ", numbers[index]);
    }
    fprintf(dst, "\n");
}

void addNumber(int *numbers, int *count, int numberToAdd) {
    debug_printf("adding number %d, current count = %d", numberToAdd, *count);
    numbers[(*count)++] = numberToAdd;
}

int main(void) {
    char *contentFilePath = "content.txt";
    FILE *contentFile;

    debug_print("STARTING");

    int numberCount = 0;
    // int numbers[CAPACITY] = {0};
    int capacity = CAPACITY;

    debug_printf("opening file '%s'", contentFilePath);
    contentFile = fopen(contentFilePath, "r");
    if (contentFile == NULL) {
        fprintf(stderr, "Failed opening file '%s'\n", contentFilePath);
        return 1;
    }

    debug_print("loading head from file");
    fscanf(contentFile, "(%d/%d) ", &numberCount, &capacity);

    debug_print("loading items from file");
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

    debug_print("saving current content to file");
    contentFile = fopen(contentFilePath, "w");
    if (contentFile == NULL) {
        fprintf(stderr, "Failed opening file '%s'\n", contentFilePath);
        return 1;
    }
    printNumbers(contentFile, numbers, numberCount, capacity);

    debug_print("terminating");
    free(numbers);
    fclose(contentFile);
    return 0;
}
