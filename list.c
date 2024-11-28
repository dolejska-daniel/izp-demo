
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list_item_t ListItem, *ListItemPtr;

typedef union {
    int integer;
    void *ptr;
} ListItemData;

struct list_item_t {
    ListItemData data;
    ListItemPtr next;
};

typedef struct {
    ListItemPtr firstItem;
} List, *ListPtr;

ListItemPtr list_add_first(ListPtr list) {
    ListItemPtr listItem = malloc(sizeof(ListItem));
    if (listItem == NULL) {
        return NULL;
    }

    listItem->next = list->firstItem;
    list->firstItem = listItem;
    return listItem;
}

bool list_remove_first(ListPtr list) {
    if (list == NULL || list->firstItem == NULL) {
        return false;
    }

    ListItemPtr firstItem = list->firstItem;
    list->firstItem = firstItem->next;
    free(firstItem);
    return true;
}

void print_list_as_int(ListPtr list) {
    ListItemPtr currentItem = list->firstItem;
    if (currentItem == NULL) {
        printf("(empty)");
    }
    while (currentItem != NULL) {
        printf("%d ", currentItem->data.integer);
        currentItem = currentItem->next;
    }
    printf("\n");
}

ListPtr list_ctor() {
    ListPtr list = malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->firstItem = NULL;
    return list;
}

void list_dtor(ListPtr *list) {
    while (list_remove_first(*list));
    free(*list);
    *list = NULL;
}

int main(void) {
    ListPtr list = list_ctor();
    print_list_as_int(list);
    list_add_first(list)->data.integer = 10;
    list_add_first(list)->data.integer = 20;
    list_add_first(list)->data.integer = 30;
    print_list_as_int(list);
    list_remove_first(list);
    list_add_first(list)->data.integer = 40;
    print_list_as_int(list);
    list_dtor(&list);
    return 0;
}
