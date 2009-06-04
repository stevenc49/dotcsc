#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIL 1000000

char* getPalin(char* num);

int main()
{
    char* num = (char*)malloc(MIL*sizeof(char));

    //num = "123456";    //read-only
    strncpy(num, "12818", MIL);

    printf("\noriginal %s\n",num );
    printf("\npalin %s\n", getPalin(num) );

    return 0;
}

char* getPalin(char* num)
{
    int length = strlen(num);

    if( length%2 == 0 )
    {
        printf("even\n");

        char* front = num;
        char* end = num + strlen(num) - 1;    //pointer to end

        //pointers not middle yet
        while( front != num + (length/2)-1 )
        {
            *end = *front;

            front++;
            end--;
        }

        //pointers at mid
        char mid[3];
        mid[0] = *front;
        mid[1] = *end;
        mid[2] = '\0';

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
    } else {
        printf("odd\n");

        char* front = num;
        char* end = num + strlen(num)-1;    //pointer to end

        //pointers not middle yet or not next to middle
        while( front != num+(length/2) && end != num+(length/2)+1 )
        {
            *end = *front;

            front++;
            end--;
        }

        //pointers next to middle (save values next to mid for comparison later)
        char mid_plus_one;
        mid_plus_one = *end;

        char mid_minus_one;
        mid_minus_one = *front;

        *end = *front;
        front++;
        end--;

        //pointers at mid
        char mid;
        mid = *front;

        printf("mid_minus_one %c\n", mid_minus_one);
        printf("*(front+1)  %c\n", *(front+1));

        if ( mid_plus_one > *(front+1))            //if old value > new value for mid_plus_one
        {                                           //then increment middle digit
            if(mid=='0') {
                *front = '1';
            } else if (mid=='1') {
                *front = '2';
            } else if (mid=='2') {
                *front = '3';
            } else if (mid=='3') {
                *front = '4';
            } else if (mid=='4') {
                *front = '5';
            } else if (mid=='5') {
                *front = '6';
            } else if (mid=='6') {
                *front = '7';
            } else if (mid=='7') {
                *front = '8';
            } else if (mid=='8') {
                *front = '9';
            } else if (mid=='9') {
                printf("i=9, carrying over");

//                *front = '0';
//                *(front-1) = mid_minus_one + 1;
//                *(end+1) = mid_minus_one + 1;
            }
        }
    }

    return num;
}
