// CSCI 3300
// Assignment: 6a
// Author:     Ibook Eyoita
// File:       trace.h
// Tab stops:  Every 4 characters

#include <cstdio>
#include <iostream>
#include <cstring>
#include "tree.h"
using namespace std;
extern int traceLevel;
// trace sets the trace levels.
void tracing(int& v,const char* opt);

// showFrequencies(arr) prints the occurences of each
// char in arr.
void showFrequencies(int* arr);

// showCharacter(char c) shows the name of c.
void showCharacter(char c);

//showCode(arr) shows the code in the arrary,arr.
void showCode(string* arr);

//printTree(theTree) prints theTree.
void printTree(Node* theTree);

//displayInfo(freq,tree,code) displays the
//frequency array,freq, the tree and the code array, code.
void displayInfo(int* freq,Node* tree, string* code);
