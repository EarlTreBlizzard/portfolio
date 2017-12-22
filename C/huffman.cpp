// CSCI 3300
// Assignment: 8
// Author:     Earl Blizzard
// File:       huffman.cpp
// Tab stops:  Every 8 characters

#include "trace.h"
#include "pqueue.h"
#include "tree.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "binary.h"
using namespace std;

//========================================================
// emptyArray(freq) fills in a zero to each block in freq[].
//========================================================

void emptyArray(int* freq)
{
	for(int count=0; count<256; count++)
	{
		freq[count]=0;
	}
}

//========================================================
//blankStringArray(arr) fills in an empty space to
//each block in arr.
//========================================================

void blankStringArray(string* arr)
{
	for(int count=0; count<256; count++)
	{
		arr[count]="";
	}
}

//========================================================
// charCount(freq,fileName) counts the frequency and 
//stores them in freq.
//========================================================

void charCount(int* freq,char* fileName)
{
	FILE* f = fopen(fileName, "r");
	
	if(f==NULL)
	{
		printf("charCount: File not opened\n");
	}
	else
	{
		emptyArray(freq);
		int c = getc(f);
		while(c!=EOF)
		{
			freq[c]++;
			c=getc(f);
		}
		fclose(f);
	}
}

//=============================================================
//megeNodes(queue) returns a nonleaf from all combined 
//nodes in the queue.
//=============================================================

Node* mergeNodes(PriorityQueue& queue)
{
	int a,b;
	Node* Tree;
	Node* d;
	remove(Tree,a,queue);
	if(!isEmpty(queue))
	{
		Node* z;
		remove(z,b,queue);
		d= new Node(Tree,z);
		insert(d,a+b,queue);
		if(traceLevel==2)
		{
			printf("merging \"%c\" with frequency of \"%i\" AND \"%c\" with frequency of  \"%i\" from the priority queue.\n",Tree->ch,a,z->ch,b);
		}
		return NULL;
	}
	printf("\n");
	return Tree;
}

//========================================================
// buildTree(freq) returns a tree corresponding to the
// frequency array freq[].
//========================================================

Node* buildTree(int* freq)
{
	PriorityQueue queue;
	for(int count=0; count<256; count++)
	{
		if(freq[count]>0)
		{
			char c=count;
			Node* x = new Node(c);
			insert(x,freq[count],queue);
			if(traceLevel==2)
			{
				printf("inserting \"%c\" into the queue with frequency of \"%i\"\n",x->ch,freq[count]);
			}
		}
	}
	printf("\n");
	while(true)   
	{
		Node* tree = mergeNodes(queue);
		if(tree!=NULL)
		{
			return tree;
		}
	}
}


//=========================================================
//buildCodeArray(codeArray,tree,path)
//stores the paths from eachleaf or non-leaf in the tree
//and puts it in the codeArray.
//=========================================================

void buildCodeArray(string* codeArray,Node* tree,string path)
{
	if(tree->kind ==nonleaf)
	{
		buildCodeArray(codeArray, tree->right, path+'1');
		buildCodeArray(codeArray, tree->left, path+'0');
	}
	else
	{
		int index= tree->ch;
		codeArray[index]=path;
	}
}

//===============================================================
//writeTreeBinary(file,tree) writes the tree into a 
//binary file.
//===============================================================

void writeTreeBinary(BFILE* file,Node* tree)
{
	if(file==NULL)
	{
		printf("writeTreeBinary: File cannot be opened\n");
	}
	else if(tree->kind ==leaf)
	{
		writeBit(file, 1);
		writeByte(file, tree->ch);
	}
	else
	{
		writeBit(file, 0);
		writeTreeBinary(file,tree->left);
		writeTreeBinary(file, tree->right);
	}
}

//===============================================================
//writeBinaryString(s,bf) writes character codes for
//the characters that are read into an open binary file,bf.
//===============================================================

void writeBinaryString(string s, BFILE* bf)
{
	for(int i=0; i<s.length(); i++)
	{
		char c= s[i];
		writeBit(bf, c-'0');
	}
}

//===============================================================
//Encode(SourceFile,bf,codeArray) writes
//the character codes of the sourceFile into the binaryFile.
//===============================================================

void Encode(const char* SourceFile, BFILE* bf,string* codeArray)
{
	FILE* f= fopen(SourceFile, "r");
	if(f==NULL)
	{
		printf("Encode: Source file not opened\n");
	}
	else if(bf==NULL)
	{
		printf("Encode: Binary file not opened\n");
	}
	else
	{
		int c=getc(f);
		while(c!=EOF)
		{
			writeBinaryString(codeArray[c],bf);
			c=getc(f);
		}
		fclose(f);
	}
}

//===============================================================
//writeEncodedFile(tree,SourceFile,binaryFile,codeArray)
//writes the tree and codeArray from the 
//sourceFile into the binaryFile.
//===============================================================

void writeEncodedFile(Node* tree,char* SourceFile,char* binaryFile, string* codeArray)
{
	FILE* f= fopen(SourceFile, "r");
	BFILE* bf= openBinaryFileWrite(binaryFile);
	writeTreeBinary(bf, tree);
	Encode(SourceFile,bf,codeArray);
	fclose(f);
	closeBinaryFileWrite(bf);
}

//===============================================================
//MAIN
//===============================================================

int main(int argc, char** argv)
{
	char* sourceFile;
	char* binaryFile;
	int* freq= new int[256];
	string* code= new string[256];
	string path="";
	if(strcmp(argv[1],"-t1")==0 || strcmp(argv[1],"-t2")==0)
	{
		tracing(traceLevel,argv[1]);
		sourceFile=argv[2];
		binaryFile=argv[3];
	}
	else
	{
		sourceFile=argv[1];
		binaryFile=argv[2];
	}
	charCount(freq,sourceFile);
	Node* tree = buildTree(freq);
	blankStringArray(code);
	buildCodeArray(code, tree, path);
	if(traceLevel==1)
	{
		displayInfo(freq,tree,code);
	}
	else if(traceLevel==2)
	{
		displayInfo(freq,tree,code);
	}
	writeEncodedFile(tree,sourceFile,binaryFile,code);
}
