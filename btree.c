#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int value;
    struct node_t *left;
    struct node_t *right;
} Node, *NodePtr;

void print_inOrder(NodePtr node) {
    if (node == NULL) {
        return;
    }

    print_inOrder(node->left);
    printf("%d ", node->value);
    print_inOrder(node->right);
}

void create_node(NodePtr *dst, int value) {
    *dst = calloc(1, sizeof(Node));
    (*dst)->value = value;
}

void insert(NodePtr node, int value) {
    if (node->value > value) {
        if (node->left != NULL){
            insert(node->left, value);
            return;
        }

        create_node(&node->left, value);
        return;
    }

    if (node->right != NULL){
        insert(node->right, value);
        return;
    }

    create_node(&node->right, value);
}

int main(void) {
    NodePtr rootNode;
    create_node(&rootNode, 10);
    insert(rootNode, 5);
    insert(rootNode, 15);

    print_inOrder(rootNode);
}
