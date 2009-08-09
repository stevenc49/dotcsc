
#include <stdio.h>

struct node
{
    int x;
    struct node *left;
    struct node *right;
};

int main()
{
    struct node *root;

    root = malloc(sizeof(struct node));
    root->x = 1;

    root->left = malloc(sizeof(struct node));
    root->left->x = 2;


    root->right = malloc(sizeof(struct node));
    root->right->x = 3;

    printf("root->left->x: %d\n", root->left->x);
    printf("root->right->x: %d\n", root->right->x);

    return 0;
}
