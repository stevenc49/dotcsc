#include <stdio.h>

int* bubble_sort(int *array, int n)
{
    int x, y = 0;
    int sorted=0; //sorted flag

    for(x=0; x<n; x++)
    {
        if (sorted==0)
        {
            for(y=0; y<n-1; y++)
            {
                sorted = 1; //assume sorted

                if(array[y]>array[y+1])
                {
                    int temp = array[y+1];
                    array[y+1] = array[y];
                    array[y] = temp;

                    sorted = 0; //if reached this if block, than not sorted in this pass
                }
            }
        }
    }

    return array;
}

int main()
{
    int i=0;
    int array[] = {1,2,3,4,5};

    bubble_sort(array, 5);

    //uses array
    for(i=0;i<5;i++)
    {
        printf("%d", array[i]);
    }

//    printf("\n");
//
//    for(i=0;i<5;i++)
//    {
//        printf("%d", *ptr);
//        ptr++;
//    }

    return 0;
}
