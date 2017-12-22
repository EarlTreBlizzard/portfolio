// CSCI 3300
// Assignment: 3
// Author:     Earl Blizzard
// File:       equiv.cpp
// Tab stops:  ***
// Libraries
#include <cstdio>
#include "equiv.h"
//createArray(length) creates an array in the heap with a length of length + 1 units,
// fills it with bosses, and returns it.

int* newEM(int length)
{
  int* bosses = new int [length+1];
  for(int k=1;k<=length+1;k++)
  {
    bosses[k]=k;
  }
  return bosses;
}

// destroy(bosses) deletes the array named bosses

void destroyEM(int* bosses)
{
  delete [] bosses;
}

//leader(bosses,worker) finds the leader of worker in the bosses array

int leader(int* bosses,int worker)
{
  if(bosses[worker]==worker)
  {
    return worker;
  }
  else
  {
    bosses[worker]=leader(bosses,bosses[worker]);
    return worker;
  }
}

//combine(bosses,first,second) combines the two groups that contain first and second.

void combine(int* bosses,int first,int second)
{
  bosses[leader(bosses,first)]=bosses[leader(bosses,second)];
}

bool together(int* bosses,int first,int second)
{
  if(leader(bosses,first)==leader(bosses,second))
  {
    return true;
  }
  return false;
}

//showEM(bosses,size) prints all of the vaues

void showEM(int* bosses,int size)
{
  for(int i=1;i<=size;i++)
  {
   printf("\t%d | %d\n",i,bosses[i]);
  }
}


