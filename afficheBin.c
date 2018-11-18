#include"afficheBin.h"
#include<stdio.h>

void affichebin(int n)
{
	int bit = 0 ;
	int mask = 1 ;
	for (int i = 0 ; i < 8 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
}
