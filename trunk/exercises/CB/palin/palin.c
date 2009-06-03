#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDIGITS 1000000

int isPalin(char num[]);
char* inc(char *num, char* p);
char* incAndCarryOver(char* num);
char* incUntilNextPalin(char *num);

main()
{
    int i, cases;

    scanf("%d", &cases);
    char* array[cases];

    //store inputs in array
    for(i=0; i<cases; i++)
    {
		char* num = malloc(MAXDIGITS);	//allocate memory dynamically
        scanf("%s", num);
        array[i] = num;
    }

    //retrieve from array and process
    for(i=0; i<cases; i++)
    {
        printf("%s\n", incUntilNextPalin( array[i] ));
    }
}

// returns 1 if palindrome, returns 0 if not a palindrome
int isPalin(char num[])
{
    char* p_num_start = num;
    char* p_num_end = num + strlen(num)-1;    //pointer to the last character of the string

    do {
        if(*p_num_start == *p_num_end)
            continue;
        else
            return 0; //not a palindrome
    } while ( p_num_start++ <= p_num_end--);

    return 1; //is a plaindrome;
}

char* inc(char *num, char* p)
{
    if( *p>='0' && *p<='8' )
    {
        (*p)++;
    }
    else if ( *p=='9' )
    {
        *p = '0';
        inc(num, --p);
    }

    return num;
}

//checks if 9,99,999... and increments if necessary
char* incAndCarryOver(char* num)
{
	int allNine = 1;	//bool allNine = true
	char* digit = num;

	while( *digit != '\0' )
	{
		if( *digit != '9')
			allNine=0;

		digit++;
	}

	//can this be refactored to be compatible with the C99 standard?
	int length = digit-num;
	char* newNum = malloc(length+1);

	//if allNine, create a new string
	//with the incremented value
	if (allNine)
	{
		int i;

		digit = newNum;
		*digit = '1';
		for( i=0 ; i<length; i++ )
		{
			digit++;
			*digit = '0';
		}
		digit++;
		*digit = '\0';

		return newNum;
	}

	return num;
}

char* incUntilNextPalin(char *num)
{
    //even if num is already a palindrome,
    //the question asks for the NEXT palindrome
    if (isPalin(num)==1)
	{
		num = incAndCarryOver(num);		//in the special cases, 9,99,999...
        inc(num, num+strlen(num)-1);
	}

    while (isPalin(num)==0)
	{
        inc(num, num+strlen(num)-1);
    }

    return num;
}
