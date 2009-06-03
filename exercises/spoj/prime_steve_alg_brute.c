#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef  unsigned long long bignum;

void printPrime(bignum bn)
	{
	static char buf[1000];

	sprintf(buf, "%ull", bn);
	buf[strlen(buf) - 2] = '\0';
	printf("%s\n", buf);
	}

void findPrimes(bignum topCandidate)
	{
	bignum candidate = 2;
	while(candidate <= topCandidate)
		{
		bignum trialDivisor = 2;
		int prime = 1;
		while(trialDivisor * trialDivisor <= candidate)
			{
			if(candidate % trialDivisor == 0)
				{
				prime = 0;
				break;
				}
			trialDivisor++;
			}
		if(prime) printPrime(candidate);
		candidate++;
		}
	}

int main(int argc, char *argv[])
	{
	bignum topCandidate = 1000;
	if(argc > 1)
		topCandidate = atoll(argv[1]);
	findPrimes(topCandidate);
	return 0;
	}

