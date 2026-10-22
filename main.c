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

void printNumbers(FILE *dst, Numbers array) {
    debug_print("printing contents");
    fprintf(dst, "(%d/%d) ", array.count, array.capacity);
    for (int index = 0; index < array.count; index++) {
        fprintf(dst, "%d ", array.items[index]);
    }
    fprintf(dst, "\n");
}

void addNumber(NumbersRef array, int numberToAdd) {
    debug_printf("adding number %d, current count = %d", numberToAdd, array->count);
    // (*array).count;
    // array[0].count;
    // array->count;
    array->items[array->count++] = numberToAdd;
}

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

    printf("&array      = %p\n", (void *)&array);
    printf("arrayRef    = %p\n", (void *)arrayRef);
    printf("&arrayRef   = %p\n", (void *)&arrayRef);
    printf("arrayRefRef = %p\n", (void *)arrayRefRef);

    debug_printf("opening file '%s'", contentFilePath);
    contentFile = fopen(contentFilePath, "r");
    if (contentFile == NULL) {
        fprintf(stderr, "Failed opening file '%s'\n", contentFilePath);
        return 1;
    }

    debug_print("loading head from file");
    fscanf(contentFile, "(%d/%d) ", &array.count, &array.capacity);

    debug_print("loading items from file");
    array.items = malloc(array.capacity * sizeof(int));
    if (array.items == NULL) {
        fprintf(stderr, "Allocation failed\n");
        fclose(contentFile);
        return 1;
    }

    for (int numberIndex = 0; numberIndex < array.count; numberIndex++) {
        fscanf(contentFile, "%d", &array.items[numberIndex]);
    }
    fclose(contentFile);

    addNumber(&array, 10);

    printNumbers(stdout, array);

    debug_print("saving current content to file");
    contentFile = fopen(contentFilePath, "w");
    if (contentFile == NULL) {
        fprintf(stderr, "Failed opening file '%s'\n", contentFilePath);
        return 1;
    }
    printNumbers(contentFile, array);

    debug_print("terminating");
    free(array.items);
    fclose(contentFile);
    return 0;
}
