#include <stdio.h>
#include <stdlib.h>

void print_items(FILE *destination, int *numbers, int max_size, int current_size) {
    fprintf(destination, "(%d/%d)", current_size, max_size);
    if (current_size == 0) {
        fprintf(destination, " There are no items.\n");
        return;
    }
    for (int i = 0; i < current_size; i++) {
        fprintf(destination, " %d", numbers[i]);
    }
    fprintf(destination, "\n");
}

void add_item_from(FILE *source, int *numbers, int max_size, int *current_size) {
    if (max_size <= *current_size) {
        fprintf(stderr, "Cannot add any more items.\n");
        return;
    }
    fscanf(source, "%d", &numbers[(*current_size)++]);
}

void prompt_add_item(int *numbers, int max_size, int *current_size) {
    fprintf(stderr, "Add item to %d. place: ", *current_size + 1);
    add_item_from(stdin, numbers, max_size, current_size);
}

void remove_last_item(int *current_size) {
    fprintf(stderr, "Removing %d. item\n", *current_size);
    (*current_size)--;
}

int *list_ctor(int max_size) {
    return malloc(max_size * sizeof(int));
}

void list_dtor(int **list) {
    free(*list);
    *list = NULL;
}

void load_from_file(FILE *source, int **numbers, int *max_size, int *current_size) {
    *current_size = 0;
    int number_count = 0;
    fscanf(source, "(%d/%d)", &number_count, max_size);
    *numbers = list_ctor(*max_size);
    for (int item_index = 0; item_index < number_count; item_index++) {
        add_item_from(source, *numbers, *max_size, current_size);
    }
}

int main(int argc, char *argv[]) {
    for (int arg_index = 0; arg_index < argc; arg_index++) {
        fprintf(stderr, "argv[%d] = %s\n", arg_index, argv[arg_index]);
    }

    if (argc < 2) {
        fprintf(stderr, "Wrong argument count, expected 2 at least\n");
        return 1;
    }

    int size = atoi(argv[1]);
    int *numbers;
    int number_count = 0;

    FILE *source = fopen("list.txt", "r");
    if (source == NULL) {
        perror("fopen() failed");
        return 1;
    }
    load_from_file(source, &numbers, &size, &number_count);

    print_items(stdout, numbers, size, number_count);
    prompt_add_item(numbers, size, &number_count);
    prompt_add_item(numbers, size, &number_count);
    prompt_add_item(numbers, size, &number_count);
    print_items(stdout, numbers, size, number_count);
    remove_last_item(&number_count);
    print_items(stdout, numbers, size, number_count);

    FILE *destination = fopen("list.txt", "w");
    if (destination == NULL) {
        perror("fopen() failed");
        list_dtor(&numbers);
        return 1;
    }

    print_items(destination, numbers, size, number_count);
    fclose(destination);

    list_dtor(&numbers);
}
