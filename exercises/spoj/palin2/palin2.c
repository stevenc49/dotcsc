#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIL 1000000

char* getPalin(char* num);
int comp(char* str1, char* str2);
char* work(char* num, int pos1, int pos2);

int main()
{
    char* num = (char*)malloc(MIL*sizeof(char));

    strncpy(num, "999", MIL);

    printf("\noriginal %s\n",num );
    printf("\npalin %s\n", getPalin(num) );

    return 0;
}

char* getPalin(char* num)
{
    int length = strlen(num);

    //save old num
    char* oldnum = malloc(MIL*sizeof(char));
    strncpy(oldnum, num, MIL);

    //set pointers
    char* front = num;
    char* end = num + strlen(num)-1;    //pointer to end

    //while pointers are not mid, mirror
    while( front != num+(length/2))
    {
        *end = *front;

        front++;
        end--;
    }

    if (comp(oldnum, num)==0)
    {
        int pos1 = front - num;
        int pos2 = end - num;

        num = work(num, pos1, pos2);
    }

    return num;
}

//increments to next palindrome
//precondition: needs to be a palindrome,
//              pos1 and pos2 must be the middle digits (or middle digit if odd)
char* work(char* num, int pos1, int pos2)
{
    if (num[pos1] < '0')
    {
        printf("overflow\n");
    }
    else if (num[pos1] < '9')
    {
        num[pos1] = num[pos2] = num[pos1] + 1;
    }
    else
    {
        num[pos1] = num[pos2] = 0;
        work(num, pos1-1, pos2+1);
    }

    return num;
}

//returns true if str2 > str1
int comp(char* str1, char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int i;

    if( len1 != len2 )
        return len1 < len2;
    for (i=0; i<len1; i++)
    {
        if (str1[i] != str2[i])
            return str1[i] < str2[i];
    }

    return 0;
}
