//Author: Earl Blizzard
//program Name: pc1.c
//tabs: 4
// date:2/20/17

//inclussions
//-----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//globals
//-----------------------------------------
#define SuperLong long int
#define size 10
SuperLong Buff[size];
int amnt=0;
int doneC=0;
#define Target (SuperLong)1000000
#define Total (SuperLong)(Target*(Target+1))/2



//prototypes
//-----------------------------------------
int consumer();
void producer();


// full functions
//-----------------------------------------
int isBuffFull()
{
	if(amnt==size)
		return 1;
	return 0;
}

int isBuffEmpty()
{
	if(amnt==0)
		return 1;
	return 0;
}

void incAmnt()
{
	amnt++;
}

void decAmnt()
{
	amnt--;
}

// consumerD() sets the value doneC to 1
// indicating that consumer is done.
void consumerD()
{
	doneC=1;
}

// isConDone() checkes to see if the consumer
// is done, if so it returns a 1 else returns 0.
int isConDone()
{
	return doneC;
}

//this is the body for tread 1
// which creates the consumer.
void* thread1()
{
	if(consumer())
		printf("all went well\n");
	else
		printf("ERROR\n");
}

//this is the body for tread 2
// which creates the producer.
void* thread2()
{
	producer();
}

//this function creates two threads and does not
//return until both have finished.
void makeThreads()
{
	pthread_t t1, t2;
	int  iret1, iret2;
	//Create independent threads each of which will execute function 
	iret1 = pthread_create( &t1, NULL, thread1,NULL);
	if(iret1)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}
	iret2 = pthread_create( &t2, NULL, thread2,NULL);
	if(iret2)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
		exit(EXIT_FAILURE);
	}	  
	pthread_join( t1, NULL);
	pthread_join( t2, NULL);	

}

