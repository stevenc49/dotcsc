#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIL 1000000

char* getPalin(char* num);

int main()
{
    char* num = (char*)malloc(MIL*sizeof(char));

    //num = "123456";    //read-only
    strncpy(num, "26516156161616549816549618616518156156189156", MIL);

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

        //pointers not middle yet
        while( front != num + (length/2)-1 )
        {
            *end = *front;

            //printf("%c", *end);

            front++;
            end--;
        }

        //pointers at mid
        char mid[3];
        mid[0] = *front;
        mid[1] = *end;
        mid[2] = '\0';

        //convert string to int
        int i = atoi(mid);

        if(i>=0 && i<11) {
            *front = '1';
            *end ='1';
        } else if (i>=11 && i<22) {
            *front = '2';
            *end ='2';
        } else if (i>=22 && i<33) {
            *front = '3';
            *end ='3';
        } else if (i>=33 && i<44) {
            *front = '4';
            *end ='4';
        } else if (i>=44 && i<55) {
            *front = '5';
            *end ='5';
        } else if (i>=55 && i<66) {
            *front = '6';
            *end ='6';
        } else if (i>=66 && i<77) {
            *front = '7';
            *end ='7';
        } else if (i>=77 && i<88) {
            *front = '8';
            *end ='8';
        } else if (i>=88 && i<99) {
            *front = '9';
            *end ='9';
        } else if (i=99)
            printf("i=99, need to carry over");
    }

    return num;
}


