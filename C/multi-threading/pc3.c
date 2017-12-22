//Author: Earl Blizzard
//program Name: pc3.c
//tabs: 4
//date:2/20/17

#include "pcHeader.h"
int Cconsumer=0;
int Cproducer=0;
#define amount (Cconsumer+Cproducer)
//main
void main()
{
	makeThreads();	
}

// consumer() reads in the buffer checking
// for the correct sequence of one through 1000000.
// this function returns 1 if it was sucessful, and 
// 0 if there was an error whilst printing the incorrect number.
int consumer()
{
	SuperLong tot = 0;
	int next = 0;
	SuperLong curr=0;
	SuperLong last=0;
	for(curr; curr<Target;)
	{
		while(amount==0);
		if(curr!=(Buff[next]-1))
		{
			printf("%llu\n",(SuperLong)Buff[next]);
			break;
		}
		curr = (SuperLong)Buff[next];
		tot=(SuperLong)(curr+tot);
		if(next==size-1)
		{
			next=0;
		}
		else
		{
			next++;
		}
		Cconsumer--;
	}
	consumerD();
	if(tot==Total)
		return 1;
	else
		return 0;
}

// producer() places values into a buffer 1 through
// 1000000 and stops once the consumer has finished
// or the number 1000000.
void producer()
{
	
	int next=0;
	SuperLong index=1;
	for(index;index<=Target;)
	{
		while(amount==size&& !isConDone());
		if(isConDone())
			break;
		Buff[next]=index;
		index=(SuperLong)index+1;
		if(next==size-1)
			next=0;
		else
			next++;
		Cproducer++;
		
	}
}
