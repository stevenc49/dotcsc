#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIL 1000000

char* getPalin(char* num);

int main()
{
    char* num = (char*)malloc(MIL*sizeof(char));

    //num = "123456";    //read-only
    strncpy(num, "123456", MIL);

    printf("%s\n", getPalin(num) );

    return 0;
}

char* getPalin(char* num)
{
    int length = strlen(num);

    if ( length % 2 == 0 )
    {
        char* front = num;
        char* end = num + strlen(num) - 1;    //pointer to end

        *end = '0';

        while( front != num + (length/2) )    //pointers not middle yet
        {
            *end = *front;

            //printf("%c", *end);

            front++;
            end--;
        }
    }

    return num;
}

