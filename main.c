#include "processing.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    bool success;
    int error_id;
} Result;

#define RESULT_OK                                                                                                      \
    (Result) {                                                                                                         \
        .success = true, .error_id = 0,                                                                                \
    }

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

#define COMMAND_ADD "add"
#define COMMAND_REMOVE "remove"
#define COMMAND_PROCESS "process"

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

void process_items_with_lib(ItemArrayPtr array) {
    process_item(&array->items[0]);
}

void add_item_from_input(ItemArrayPtr array) {
    int value;
    printf("Input a value to add: ");
    scanf("%d", &value);
    add_item(array, value);
}

void remove_items(ItemArrayPtr array, int count) {
    array->currentCount = array->currentCount < count ? 0 : array->currentCount - count;
}

Result find_minMax(ItemArrayPtr array, int *min, int *max) {
    if (array->currentCount == 0) {
        return RESULT_OK;
    }

    *min = array->items[0];
    *max = array->items[0];
    for (int itemIndex = 1; itemIndex < array->currentCount; itemIndex++) {
        int currentItem = array->items[itemIndex];
        if (currentItem < *min) {
            *min = currentItem;
        }
        if (currentItem > *max) {
            *max = currentItem;
        }
    }

    return RESULT_OK;
}

typedef void (*action)(ItemArrayPtr);

typedef struct {
    char name[10];
    char desc[40];
    action callback;
} ActionDefinition;

typedef struct {
    ActionDefinition items[10];
    int length;
} ActionDefinitions;

int main(void) {
    FILE *file;
    ItemArray numbers = {
        .items = NULL,
        .capacity = 0,
        .currentCount = 0,
    };

    ActionDefinitions actions = {
        .items = {{.name = COMMAND_ADD, .desc = "Adds item to the array", .callback = &add_item_from_input},
                  {.name = COMMAND_PROCESS, .desc = "Process with library", .callback = &process_items_with_lib}},
        .length = 2,
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

    char input[100];
    do {
        print_contents(stdout, &numbers);
        for (int actionIndex = 0; actionIndex < actions.length; actionIndex++) {
            ActionDefinition action = actions.items[actionIndex];
            printf("%9s) %s\n", action.name, action.desc);
        }
        printf("%9s) %s\n", "exit", "Closes the program");
        scanf("%99s", input);
        bool handled = false;
        for (int actionIndex = 0; actionIndex < actions.length; actionIndex++) {
            ActionDefinition action = actions.items[actionIndex];
            if (strcmp(action.name, input) == 0) {
                action.callback(&numbers);
                handled = true;
                break;
            }
        }
        if (handled) {
            continue;
        }
        if (strcmp("exit", input) == 0) {
            break;

        } else {
            fprintf(stderr, "Unknown command: %s\n", input);
            continue;
        }
    } while (true);

    int min = 0, max = 0;
    if (find_minMax(&numbers, &min, &max).success) {
        printf("min = %d, max = %d\n", min, max);
    }

    print_contents(stdout, &numbers);

    file = fopen(FILE_NAME, "w");
    print_contents(file, &numbers);

    debug_print("Closing file");
    fclose(file);

    free(numbers.items);
    return 0;
}
