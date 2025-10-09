#include <stdio.h>
#include <stdlib.h>

#define ARRAY_CAPACITY 10
#define FILE_NAME "list.txt"
#define FILE_ARRAY_COUNT_TEMPLATE "There are %d/%d items.\n"

struct ItemArray {
    int *items;
    int capacity;
    int currentCount;
};

void print_contents(FILE *file, struct ItemArray *array) {
    fprintf(file, FILE_ARRAY_COUNT_TEMPLATE, array->currentCount, array->capacity);
    for (int index = 0; index < array->currentCount; index++) {
        fprintf(file, "item[%d] = %d\n", index, array->items[index]);
    }
}

void load_contents(FILE *file, struct ItemArray *array) {
    fscanf(file, FILE_ARRAY_COUNT_TEMPLATE, &(*array).currentCount, &array->capacity);
    array->items = malloc(sizeof(*array->items) * array->capacity);
    if (array->items == NULL) {
        printf("ERR: Failed to allocate memory");
        array->capacity = 0;
        array->currentCount = 0;
    }

    for (int line = 0; line < array->currentCount; line++) {
        int scanned = fscanf(file, "item[%*d] = %d\n", &array->items[line]);
        printf("scanf() == %d\n", scanned);
    }
}

void add_item(struct ItemArray *array, int value) {
    if (array->capacity <= array->currentCount + 1) {
        array->items = realloc(array->items, sizeof(*array->items) * array->capacity * 2);
    }

    array->items[array->currentCount++] = value;
}

int main(void) {
    FILE *file;
    struct ItemArray numbers = {
        .items = NULL,
        .capacity = 0,
        .currentCount = 0,
    };

    file = fopen(FILE_NAME, "r");
    if (file != NULL) {
        load_contents(file, &numbers);
        fclose(file);
    } else {
        return 1;
    }

    add_item(&numbers, 10);
    print_contents(stdout, &numbers);

    file = fopen(FILE_NAME, "w");
    print_contents(file, &numbers);
    fclose(file);

    free(numbers.items);
    return 0;
}
