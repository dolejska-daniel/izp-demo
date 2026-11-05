#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define debug_printf(format, ...)                                                                                      \
    fprintf(stderr, "%s:%d | %s | " format "\n", __FILE__, __LINE__, __func__, __VA_ARGS__)

#define debug_print(format) debug_printf("%s", format)
#else
#define debug_printf(...)                                                                                              \
    while (0) {                                                                                                        \
    }
#define debug_print(x)                                                                                                 \
    while (0) {                                                                                                        \
    }
#endif

#define CAPACITY 5

struct tree_node_t {
    int value;
    struct tree_node_t *left;
    struct tree_node_t *right;
};

typedef struct {
    int *items;
    int count;
    int capacity;
} Numbers;
typedef Numbers *NumbersRef;

typedef struct {
    char *description;
    void (*run)(NumbersRef);
} OptionItem;

bool numbers_ctor(NumbersRef numbers, int capacity) {
    numbers->count = 0;
    numbers->items = malloc(capacity * sizeof(*numbers->items));
    if (numbers->items == NULL) {
        numbers->capacity = 0;
        return false;
    }

    numbers->capacity = capacity;
    return true;
}

void numbers_dtor(NumbersRef numbers) {
    free(numbers->items);
    numbers->items = NULL;
    numbers->capacity = 0;
    numbers->count = 0;
}

void printNumbers(FILE *dst, Numbers array) {
    debug_print("printing contents");
    fprintf(dst, "(%d/%d) ", array.count, array.capacity);
    for (int index = 0; index < array.count; index++) {
        fprintf(dst, "%d ", array.items[index]);
    }
    fprintf(dst, "\n");
}

bool addNumber(NumbersRef array, int numberToAdd) {
    debug_printf("adding number %d, current count = %d", numberToAdd, array->count);
    if (array->count >= array->capacity) {
        int newCapacity = array->capacity * 2;
        int *newItems = realloc(array->items, newCapacity * sizeof(*array->items));
        if (newItems == NULL) {
            debug_printf("failed reallocating items to new capacity %d -> %d", array->capacity, newCapacity);
            return false;
        }

        array->capacity = newCapacity;
        array->items = newItems;
    }

    array->items[array->count++] = numberToAdd;
    return true;
    ;
}

void addNumberInteractive(NumbersRef array) {
    printf("Input a number to add: ");
    int input;
    scanf("%d", &input);
    addNumber(array, input);
}

bool removeNumber(NumbersRef array, int indexToRemove) {
    debug_printf("removing number on index %d, current count = %d", indexToRemove, array->count);
    if (indexToRemove < 0 || indexToRemove >= array->count) {
        return false;
    }

    for (int index = indexToRemove; index < array->count - 1; index++) {
        array->items[index] = array->items[index + 1];
    }

    array->count--;

    if (array->count < array->capacity / 2) {
        int newCapacity = array->capacity / 2;
        int *newItems = realloc(array->items, newCapacity * sizeof(*array->items));
        if (newItems == NULL) {
            debug_printf("failed reallocating items to new capacity %d -> %d", array->capacity, newCapacity);
            return false;
        }

        array->capacity = newCapacity;
        array->items = newItems;
    }

    return true;
}

void removeNumberInteractive(NumbersRef array) {
    for (int index = 0; index < array->count; index++) {
        printf("%d) %d\n", index, array->items[index]);
    }
    printf("Input a number to remove: ");
    int input;
    scanf("%d", &input);
    removeNumber(array, input);
}

#define OPTION_COUNT 4

int main(void) {
    char *contentFilePath = "content.txt";
    FILE *contentFile;

    debug_print("STARTING");

    Numbers array = {
        .capacity = CAPACITY,
        .items = NULL,
        .count = 0,
    };

    Numbers *arrayRef = &array;        // struct NumbersArray *
    Numbers **arrayRefRef = &arrayRef; // struct NumbersArray **
    arrayRef = *arrayRefRef;           // struct NumbersArray *
    array = *arrayRef;                 // struct NumbersArray

    // printf("&array      = %p\n", (void *)&array);
    // printf("arrayRef    = %p\n", (void *)arrayRef);
    // printf("&arrayRef   = %p\n", (void *)&arrayRef);
    // printf("arrayRefRef = %p\n", (void *)arrayRefRef);

    debug_printf("opening file '%s'", contentFilePath);
    contentFile = fopen(contentFilePath, "r");
    if (contentFile == NULL) {
        fprintf(stderr, "Failed opening file '%s'\n", contentFilePath);
        return 1;
    }

    debug_print("loading head from file");
    fscanf(contentFile, "(%d/%d) ", &array.count, &array.capacity);

    debug_print("loading items from file");
    if (!numbers_ctor(&array, array.capacity)) {
        fprintf(stderr, "Allocation failed\n");
        fclose(contentFile);
        return 1;
    }

    for (int numberIndex = 0; numberIndex < array.count; numberIndex++) {
        fscanf(contentFile, "%d", &array.items[numberIndex]);
    }
    fclose(contentFile);

    OptionItem options[OPTION_COUNT] = {{.description = "Add a number", .run = &addNumberInteractive},
                                        {.description = "Remove a number", .run = &removeNumberInteractive},
                                        {.description = "Remove a number", .run = &removeNumberInteractive},
                                        {.description = "Remove a number", .run = &removeNumberInteractive}};

    while (true) {
        int option;

        printNumbers(stdout, array);
        for (int index = 0; index < OPTION_COUNT; index++) {
            OptionItem optionItem = options[index];
            printf("%d) %s\n", index + 1, optionItem.description);
        }
        printf("9) Exit\n");
        printf("Enter an option number: ");
        scanf("%d", &option);
        int optionIndex = option - 1;

        if (optionIndex >= 0 && optionIndex < OPTION_COUNT) {
            OptionItem optionItem = options[optionIndex];
            optionItem.run(&array);
        }

        switch (option) {
        case 9:
            printf("Baii.\n");
            break;

        default:
            printf("Unknown option: %d.\n", option);
            continue;
        }

        break;
    }

    debug_print("saving current content to file");
    contentFile = fopen(contentFilePath, "w");
    if (contentFile == NULL) {
        fprintf(stderr, "Failed opening file '%s'\n", contentFilePath);
        return 1;
    }
    printNumbers(contentFile, array);

    debug_print("terminating");
    numbers_dtor(&array);
    fclose(contentFile);
    return 0;
}
