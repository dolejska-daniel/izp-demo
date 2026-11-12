#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_node_t {
    int value;
    struct tree_node_t *left;
    struct tree_node_t *right;
};

void print_in_order(struct tree_node_t *root) {
    if (root == NULL) {
        return;
    }

    print_in_order(root->left);
    printf("%d ", root->value);
    print_in_order(root->right);
}

// factorial(5)
//  5 * factorial(4)
//    4 * factorial(3)
//     3 * factorial(2)
//       2 * factorial(1)
//         1 * factorial(0)
//           1 * 1

long factorial(long n) {
    if (n == 0) {
        return 1;
    }

    return n * factorial(n - 1);
}

long factorial_tail(long n, long acc) {
    if (n == 0) {
        return acc;
    }

    return factorial_tail(n - 1, n * acc);
}

int main(void) {
    long n;
    printf("Calculate factoral of: ");
    scanf("%li", &n);

    printf("%li! = %li\n", n, factorial(n));
    printf("%li! = %li\n", n, factorial_tail(n, 1));
}
