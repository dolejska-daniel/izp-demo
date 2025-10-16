#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG_PRINT
#define debug_printf(format, ...)                                                                                      \
    fprintf(stderr, "%s:%d | %s | " format "\n", __FILE__, __LINE__, __func__, __VA_ARGS__)
#else
#define debug_printf(format, ...)                                                                                      \
    while (0) {                                                                                                        \
        fprintf(stderr, format, __VA_ARGS__);                                                                          \
    }
#endif
#define debug_print(message) debug_printf("%s", message)

#define ARRAY_CAPACITY 10
#define FILE_NAME "list.txt"
#define FILE_ARRAY_COUNT_TEMPLATE "There are %d/%d items.\n"

typedef struct {
    int *items;
    int capacity;
    int currentCount;
} ItemArray, *ItemArrayPtr;

void print_contents(FILE *file, ItemArrayPtr array) {
    debug_print("Printing");
    fprintf(file, FILE_ARRAY_COUNT_TEMPLATE, array->currentCount, array->capacity);
    for (int index = 0; index < array->currentCount; index++) {
        fprintf(file, "item[%d] = %d\n", index, array->items[index]);
    }
}

void load_contents(FILE *file, ItemArrayPtr array) {
    debug_print("Loading contents from file");
    fscanf(file, FILE_ARRAY_COUNT_TEMPLATE, &(*array).currentCount, &array->capacity);
    array->items = malloc(sizeof(*array->items) * array->capacity);
    if (array->items == NULL) {
        printf("ERR: Failed to allocate memory");
        array->capacity = 0;
        array->currentCount = 0;
    }

    for (int line = 0; line < array->currentCount; line++) {
        int scanned = fscanf(file, "item[%*d] = %d\n", &array->items[line]);
        debug_printf("scanf() == %d", scanned);
    }
}

void add_item(ItemArrayPtr array, int value) {
    debug_printf("Adding item: %d", value);
    if (array->capacity <= array->currentCount + 1) {
        debug_print("Resizing array");
        array->items = realloc(array->items, sizeof(*array->items) * array->capacity * 2);
    }

    array->items[array->currentCount++] = value;
}

int main(void) {
    FILE *file;
    ItemArray numbers = {
        .items = NULL,
        .capacity = 0,
        .currentCount = 0,
    };

    debug_print("Loading from file");
    file = fopen(FILE_NAME, "r");
    if (file != NULL) {
        load_contents(file, &numbers);
        debug_print("Closing file");
        fclose(file);
    } else {
        return 1;
    }

    add_item(&numbers, 10);
    print_contents(stdout, &numbers);

    file = fopen(FILE_NAME, "w");
    print_contents(file, &numbers);

    debug_print("Closing file");
    fclose(file);

    free(numbers.items);
    return 0;
}
