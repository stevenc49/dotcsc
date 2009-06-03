#include <stdio.h>

main()
{
	int i, n, palin, cases;
	
	scanf("%d", &cases);

	int array[cases];
	
	//store inputs in array
	for(i=0; i<cases; i++)
	{
		scanf("%d", &n);
		array[i] = n;
	}

	//retrieve from array and process
	for(i=0; i<cases; i++)
	{
		n = array[i];
		palin = incUntilNextPalin(&n);
		printf("%d\n", palin);
	}
	
	return 0;
}

// returns 1 if palindrome, returns 0 if not a palindrome
int isPalin(int num_int)
{
	static char num_ary[1000000];
	
	sprintf(num_ary, "%d", num_int); //convert int to string
	
	char* p_num_start 	= num_ary;
	char* p_num_end		= num_ary + strlen(num_ary)-1;	//pointer to the last character of the string
	
	do {
		if(*p_num_start == *p_num_end)
			continue;
		else
			return 0; //not a palindrome
	} while ( p_num_start++ <= p_num_end--);
	
	return 1; //is a plaindrome;
}

int incUntilNextPalin(int *num)
{
	if (isPalin(*num)==1)
		(*num)++;

	while (isPalin(*num)==0)
	{
		(*num)++;
	}
	
	return *num;
}
