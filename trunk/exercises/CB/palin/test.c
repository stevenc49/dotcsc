#include <stdio.h>

main()
{
    int i, cases;
    char num[1000000];

    scanf("%d", &cases);
    char* array[cases];

    //store inputs in array
    for(i=0; i<cases; i++)
    {
        scanf("%s", &num);
        array[i] = num;
    }

    //print out array items and their memory addresses
    for(i=0; i<cases; i++)
    {
        printf("%d %s\n", i, array[i]);
        printf("%d %p\n", i, &array[i]);
    }
}
