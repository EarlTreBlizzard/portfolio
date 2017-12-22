// CSCI 3300
// Assignment: 5
// Author:     Earl Blizzard
// File:       pqueue.cpp
// Tab stops:  ***

// creates and manages a Priority Queue.

#include "pqueue.h"
#include <cstdio>
using namespace std;


typedef  PriorityQueue* PQ;

//tells wether or not if priority queue is empty.

bool priority::isEmpty(const PriorityQueue& q)
{
	if(q.next==NULL)
	{
	return true;
	}
	return false;
}

//Insert a new item with a set priority into the priority queue.



void priority::insert(PriorityQueue& q,  const PQItemType& x,  PQPriorityType p)
{
	if(q.next==NULL)
	{
		PQ nCell = new PriorityQueue (NULL,x,p);
		q.next = nCell;
	}
	if(x<q.next->item)
	{
		PQ nCell =new PriorityQueue(q.next,x,p);
		q.next = nCell;
	}
	else
	{
		insert(q,x,p);
	}
}

//Remove the item from the priority queue that has the smallest priority.
//and gives back the item and the priority.

void priority::remove(PriorityQueue& q,  PQItemType& x,  PQPriorityType& p)
{
	PQ front= q.next;
	x=q.item;
	p=q.Priority;
	q.next=q.next->next;
	delete front;
}

//Print the contents of the priority queue, from lowest priority to highest priority, to the standard output.

void priority::printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp)
{
	PQ scanCell = q.next;
        while(scanCell->next != NULL)
        {
                pp(scanCell->Priority);
                printf("        ");
                pi(scanCell->item);
                printf("\n");
                scanCell = scanCell->next;
        }	
}
