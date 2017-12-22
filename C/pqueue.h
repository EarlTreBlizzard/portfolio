// CSCI 3300
// Assignment: 5
// Author:     Earl Blizzard
// File:       pqueue.h
// Tab stops:  ***

// **Say what this program does here.  (replace this comment)**


#ifndef pqueue_h
#define pqueue_h
#include <cstddef>
using namespace std;

typedef const char* PQItemType;
typedef double      PQPriorityType;
typedef void (ItemPrinter)(const PQItemType&);
typedef void (PriorityPrinter)(PQPriorityType);

struct PriorityQueue
{
	PriorityQueue* next;
	PQItemType item;
	PQPriorityType Priority;
	PriorityQueue(PriorityQueue* n, PQItemType I,PQPriorityType p)
	{
		next = n;
		item = I;
		Priority = p;
	}
	PriorityQueue()
	{
		next = NULL;
	}
};
class priority
{
	public:
	//return true if priority queue is empty.

	bool isEmpty(const PriorityQueue& q);

	//Insert a new item with a set priority into the priority queue.

	void insert(PriorityQueue& q,  const PQItemType& x,  PQPriorityType p);	

	//Remove the item from the priority queue that has the smallest priority.
	//and gives back the item and the priority.
	
	void remove(PriorityQueue& q,  PQItemType& x,  PQPriorityType& p);

	//Print the contents of the priority queue, from lowest priority to highest priority, to the standard output.

	void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp);
	private:
};
#endif
