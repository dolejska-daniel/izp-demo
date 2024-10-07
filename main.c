#include<stdio.h>
#include<stdlib.h>

void print_items(int *numbers, int current_size) {
    printf("(%d)", current_size);
    if (current_size == 0) { 
        printf(" There are no items.\n");
        return;
    }
    for (int i = 0; i < current_size; i++) {
        printf(" %d", numbers[i]);
    }
    printf("\n");
}

void add_item(int *numbers, int max_size, int *current_size) {
    if (max_size <= *current_size) {
        printf("Cannot add any more items.\n");
        return;
    }
    printf("Add item to %d. place: ", *current_size + 1);
    scanf("%d", &numbers[(*current_size)++]);
}

void remove_last_item(int *current_size) {
    printf("Removing item %d\n", *current_size);
    (*current_size)--;
}

int main(int argc, char *argv[])
{
    for (int arg_index = 0; arg_index < argc; arg_index++)
    {
        printf("argv[%d] = %s\n", arg_index, argv[arg_index]);
    }

    if (argc < 2)
    {
        printf("Wrong argument count, expected 2 at least\n");
        return 1;
    }

    int size = atoi(argv[1]);
    int *numbers = malloc(size * sizeof(int));
    int number_count = 0;

    print_items(numbers, number_count);
    add_item(numbers, size, &number_count);
    add_item(numbers, size, &number_count);
    add_item(numbers, size, &number_count);
    print_items(numbers, number_count);
    remove_last_item(&number_count);
    print_items(numbers, number_count);

    free(numbers);
}
