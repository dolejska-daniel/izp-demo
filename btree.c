#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t Node, *NodePtr;

struct node_t {
    int data;
    NodePtr left;
    NodePtr right;
};

NodePtr node_ctor(int data)
{
    NodePtr node = malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void tree_insert(NodePtr subtree, int data)
{
    if (subtree->data < data)
    {
        // insert to the right subtree
        if (subtree->right == NULL)
        {
            subtree->right = node_ctor(data);
        }
        else
        {
            tree_insert(subtree->right, data);
        }
    }
    else if (subtree->data > data)
    {
        // insert to the left subtree
        if (subtree->left == NULL)
        {
            subtree->left = node_ctor(data);
        }
        else
        {
            tree_insert(subtree->left, data);
        }
    }
}

void tree_insert_iter(NodePtr treeRoot, int data)
{
    NodePtr currentNode = treeRoot;
    while (currentNode != NULL) {
        if (currentNode->data < data)
        {
            // insert to the right subtree
            if (currentNode->right == NULL)
            {
                currentNode->right = node_ctor(data);
                currentNode = NULL;
            }
            else
            {
                currentNode = currentNode->right;
            }
        }
        else if (currentNode->data > data)
        {
            // insert to the left subtree
            if (currentNode->left == NULL)
            {
                currentNode->left = node_ctor(data);
                currentNode = NULL;
            }
            else
            {
                currentNode = currentNode->left;
            }
        }
        else
        {
            break;
        }
    }
}

void print_tree_in_order(NodePtr subtree)
{
    if (subtree->left != NULL)
    {
        print_tree_in_order(subtree->left);
    }

    printf("%d\n", subtree->data);

    if (subtree->right != NULL)
    {
        print_tree_in_order(subtree->right);
    }
}

void print_tree_in_order_iter(NodePtr subtree)
{
    // would need stack or parent pointer
}

int main()
{
    NodePtr treeRoot = node_ctor(10);
    tree_insert(treeRoot, 7);
    tree_insert(treeRoot, 15);
    tree_insert(treeRoot, 3);
    tree_insert(treeRoot, 8);
    tree_insert(treeRoot, 20);

    print_tree_in_order(treeRoot);

    return 0;
}
