
#include <stdio.h>

int* selection_sort(int *array, int n)
{
    int x, y = 0;

    for(x=0; x<n; x++)
    {
        int index_of_min = x;

        for(y=x; y<n; y++)
        {
            if(array[index_of_min]<array[y])    //sort big to small
                index_of_min = y;
        }

        int temp = array[x];
        array[x] = array[index_of_min];
        array[index_of_min]=temp;
    }

    return array;
}

int main()
{
    int i;
    int array[] = {2,3,1,5,4};

    selection_sort(array, 5);

    for(i=0;i<5;i++)
        printf("%d", array[i]);

    return 0;
}
