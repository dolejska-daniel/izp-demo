#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG_PRINT
#define printf_debug(format, ...)                                                                                      \
    fprintf(stderr, "%s:%-4d | %15s | " format "\n", __FILE__, __LINE__, __func__, __VA_ARGS__)
#else
#define printf_debug(format, ...) (0)
#endif
#define print_debug(text) printf_debug("%s", text)
#define print_debug_list(list)                                                                                         \
    printf_debug("item_count=%d, capacity=%d", (((ListPtr)list)->item_count), (((ListPtr)list)->capacity));

#define FILEPATH "list.txt"

enum ActivityOptions { OptionPrint = 1, OptionAdd, OptionRemoveLast, OptionQuit };

typedef struct {
    int capacity;
    int item_count;
    int *items;
} List, *ListPtr;

void list_expand(ListPtr list);

void print_items(FILE *destination, ListPtr list) {
    fprintf(destination, "(%d/%d)", list->item_count, list->capacity);
    if (list->item_count == 0) {
        fprintf(destination, " There are no items.\n");
        return;
    }
    for (int item_index = 0; item_index < list->item_count; item_index++) {
        fprintf(destination, " %d", list->items[item_index]);
    }
    fprintf(destination, "\n");
}

void add_item_from(FILE *source, ListPtr list) {
    if (list->capacity <= list->item_count) {
        list_expand(list);
    }
    fscanf(source, "%d", &list->items[list->item_count++]);
    print_debug_list(list);
}

void prompt_add_item(ListPtr list) {
    print_debug("loading next item from stdin");
    fprintf(stdout, "Add item to %d. place: ", list->item_count + 1);
    add_item_from(stdin, list);
}

void remove_last_item(ListPtr list) {
    print_debug_list(list);
    if (list->item_count == 0) {
        print_debug("nothing to remove from empty list");
        return;
    }
    fprintf(stdout, "Removing %d. item\n", list->item_count + 1);
    list->item_count--;
}

ListPtr list_ctor(int capacity) {
    ListPtr list = (ListPtr)malloc(sizeof(List));
    printf_debug("created new list of size %d at %p", capacity, (void *)list);
    if (list == NULL) {
        perror("could not create List");
        return NULL;
    }
    list->capacity = capacity;
    list->item_count = 0;
    list->items = (int *)malloc(capacity * sizeof(int));

    return list;
}

void list_dtor(ListPtr *list) {
    printf_debug("destroying list at %p", (void *)list);
    free((*list)->items);
    free(*list);
    *list = NULL;
}

void list_expand(ListPtr list) {
    list->capacity *= 2;
    list->items = realloc(list->items, sizeof(int) * list->capacity);
    if (list->items == NULL) {
        print_debug("list expansion failed!");
    }
}

void load_from_file(FILE *source, ListPtr *list) {
    int item_count = 0, capacity = 0;
    fscanf(source, "(%d/%d)", &item_count, &capacity);
    printf_debug("loaded from file: item_count=%d, capacity=%d", item_count, capacity);

    *list = list_ctor(capacity);
    for (int item_index = 0; item_index < item_count; item_index++) {
        printf_debug("loading item %d", item_index);
        add_item_from(source, *list);
    }
}

void print_menu(void) {
    printf("Select an action:\n");
    printf("  %d) Print current list\n", OptionPrint);
    printf("  %d) Add an time to list\n", OptionAdd);
    printf("  %d) Remove last item\n", OptionRemoveLast);
    printf("  %d) Quit\n", OptionQuit);
}

bool prompt_menu_option(ListPtr list) {
    int option;
    scanf("%d", &option);
    switch (option) {
    case OptionPrint: {
        print_items(stdout, list);
        break;
    }
    case OptionAdd:
        prompt_add_item(list);
        break;
    case OptionRemoveLast:
        remove_last_item(list);
        break;
    case OptionQuit:
        return false;
    default:
        printf("Unknown option %d. Try again?\n", option);
        break;
    }

    return true;
}

int main(int argc, char *argv[]) {
    for (int arg_index = 0; arg_index < argc; arg_index++) {
        printf_debug("argv[%d] = %s", arg_index, argv[arg_index]);
    }

    if (argc < 2) {
        fprintf(stdout, "Wrong argument count, expected 2 at least\n");
        return 1;
    }

    int size = atoi(argv[1]);
    ListPtr list = list_ctor(size);
    if (list == NULL) {
        print_debug("list allocation failed");
        return 1;
    }

    printf_debug("opening file: %s", FILEPATH);
    FILE *source = fopen(FILEPATH, "r");
    if (source != NULL) {
        printf_debug("file opened, reading from: %s", FILEPATH);
        load_from_file(source, &list);
    }

    bool is_running = true;
    while (is_running) {
        print_menu();
        is_running = prompt_menu_option(list);
    }

    printf_debug("opening file: %s", FILEPATH);
    FILE *destination = fopen(FILEPATH, "w");
    if (destination == NULL) {
        perror("fopen() failed");
        list_dtor(&list);
        return 1;
    }

    printf_debug("storing list to file: %s", FILEPATH);
    print_items(destination, list);

    printf_debug("closing file: %s", FILEPATH);
    fclose(destination);

    list_dtor(&list);
}
