
#include <stdio.h>

struct node {
    int x;
    struct node *next;
};

int main()
{
    struct node *root;
    struct node *conductor;

    root = malloc(sizeof(struct node));
    root->x = 1;

    conductor = root;

    int i;

    for(i=0; i<=5; i++)
    {
        conductor->next = malloc(sizeof(struct node));
        conductor->x = i;

        conductor=conductor->next;
    }

    conductor->x = -1; //end the list

    //run thru entire list
    conductor = root;

    while(conductor->x >= 0)
    {
        printf("x: %d\n", conductor->x);
        conductor=conductor->next;
    }

    return 0;
}
