// CSCI 3300
// Assignment: 3
// Author:     ***
// File:       equiv.h
// Tab stops:  ***

// These #ifndef and #define lines make it so that, if this file is
// read more than once by the compiler, its body is skipped on all
// but the first time it is read.

#ifndef EQUIV_H
#define EQUIV_H

// An equivalence manager is an array of integers.  So EM abbreviates int*.  
typedef int* EM;

EM   newEM    (int n);
void destroyEM(EM e);
bool together (EM e, int x, int y);
void combine  (EM e, int x, int y);

// The following is advertised here solely for debugging.  These must
// only be used for debugging.

void showEM(EM e, int n);
int  leader(EM e, int x);

#endif
