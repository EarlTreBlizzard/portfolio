// CSCI 3300
// Assignment: 8
// Author:     Earl Blizzard
// File:       unhuffman.cpp
// Tab stops:  Every 8 characters

#include "trace.h"
#include "tree.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "binary.h"
using namespace std;

//===============================================================
//readTree(bf) reads the tree from binary file bf.
//===============================================================

Node* readTree(BFILE* bf)
{
	int bit=readBit(bf);
	if(bit==1)
	{
		.
		int c = readByte(bf);
		return new Node(c);
	}
	else
	{
		
		Node* L= readTree(bf);
		Node* R= readTree(bf);
		return new Node(L,R);
	}
}

//===============================================================
//Decode(bf,tree,f,root) reads character 
//codes from bf and writes those characeters into F. root is the 
//huffman tree's root and tree will be the current Node.
//===============================================================

void Decode(BFILE* bf,Node* tree,FILE* f,Node* root)
{
	if(tree->kind == leaf)
	{
		fprintf(f,"%c",tree->ch);
		Decode(bf, root,f,root);
	}
	else
	{
		int c= readBit(bf);
		if(c!=EOF)
		{
			if(c==0)
			{
				Decode(bf, tree->left,f,root);
			}
			else
			{
				Decode(bf,tree->right,f,root);
			}
		}
	}
}

//===============================================================
//MAIN
//===============================================================

int main(int argc, char** argv)
{
	Node* tree;
	char* binaryFile;
	char* decodedFile;
	if(strcmp(argv[1],"-t1")==0 || strcmp(argv[1],"-t2")==0)
	{
		tracing(traceLevel,argv[1]);
		binaryFile= argv[2];
		decodedFile= argv[3];
	}
	else
	{
		binaryFile=argv[1];
		decodedFile=argv[2];
	}
	BFILE* bf = openBinaryFileRead(binaryFile);
	FILE* f= fopen(decodedFile, "w");
	if(bf==NULL)
	{
		printf("Unhuffman Main: Cannot open binary file.\n");
	}
	else if(f==NULL)
	{
		printf("Unhuffman Main: Cannot open decoded file.\n");
	}
	else
	{
		tree= readTree(bf);
		printf("The decoded huffman tree is as follows\n");
		printTree(tree);
		printf("\n");
		Decode(bf,tree,f,tree);
	}
	closeBinaryFileRead(bf);
	fclose(f);
}
