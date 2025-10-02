#include <stdio.h>

#define ARRAY_CAPACITY 10
#define FILE_NAME "list.txt"
#define FILE_ARRAY_COUNT_TEMPLATE "There are %d items.\n"

void print_contents(FILE *file, int items[ARRAY_CAPACITY], int count) {
    fprintf(file, FILE_ARRAY_COUNT_TEMPLATE, count);
    for (int index = 0; index < count; index++) {
        fprintf(file, "item[%d] = %d\n", index, items[index]);
    }
}

int load_contents(FILE *file, int items[ARRAY_CAPACITY]) {
    int loadedCount;
    fscanf(file, FILE_ARRAY_COUNT_TEMPLATE, &loadedCount);
    for (int line = 0; line < loadedCount; line++) {
        int scanned = fscanf(file, "item[%*d] = %d\n", &items[line]);
        printf("scanf() == %d\n", scanned);
    }

    return loadedCount;
}


int main(void) {
    FILE *file;
    int numbers[ARRAY_CAPACITY] = {0};
    int numbersCount = 0;

    file = fopen(FILE_NAME, "r");
    if (file != NULL) {
        numbersCount = load_contents(file, numbers);
        fclose(file);
    }

    numbers[numbersCount++] = 10;
    print_contents(stdout, numbers, numbersCount);

    file = fopen(FILE_NAME, "w");
    print_contents(file, numbers, numbersCount);
    fclose(file);

    return 0;
}
