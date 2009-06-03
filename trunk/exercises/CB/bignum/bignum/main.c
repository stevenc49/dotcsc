#include <stdio.h>

struct bignum {
    int value[1000000];
    int len;
}

int main()
{
    struct bignum *x;

    (*x).value[0] = 2;

    printf("%d\n", (*x).value[0]);

    return 0;
}
