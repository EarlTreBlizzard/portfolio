// Author: Earl Blizzard
// Date: 3/24/17
// asssinment: fileSize.c
// tab size: 4

//inclusions
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//prototypes
int dirSize(char*,char*);
int sizeOf(char*,char*);
char* apend(char*,char*);

//void main(int argc,char* argv[]) gathers informaton about the file size, and
// then displays it.
void main(int argc,char* argv[])
{
	int size = 0;
	if(argc > 1)
	{
		size = dirSize(argv[1], ".");
	}
	else
	{
		printf("ERROR: no file was selected\n");
		exit(0);
	}

	printf("the number of bytes used by all regular files in %s:\n",argv[1]);
	printf("%i bytes\n",size);
	printf("%i kilobytes\n" , size/1000);
	printf("%i megabytes\n" , (size/1000)/1000);
}

//int dirSize(char* dirName, char* path), find the amount of bytes 
// used by a directory and returns that value dirName is the name of the file
// being accessed path is the path to the file.
int dirSize(char* dirName, char* path)
{
	// VARs
	int size = 0;
	DIR* opDir;
	struct dirent* reader;
	// Opens directory
	opDir = opendir(apend(dirName,path));
	//checks to see if the file is there
	// if not the size is zero
	if(opDir == NULL)
	{
		printf("ERROR the selected directory does not exit\n");
		return 0;
	}
	//begins reading the directory
	reader = readdir(opDir);
	// runs until there is no items left
	// in the directory
	while(reader != NULL)
	{
		if(strcmp(reader->d_name,".") != 0 && strcmp(reader->d_name,"..") != 0)
		{
			size += sizeOf(reader->d_name,apend(dirName,path));
		}
		reader = readdir(opDir);
	}
	// closes the open directory
	closedir(opDir);
	//returns the size of the file
	return size;
}

// int sizeOf(char* fileName, char* path) finds the size of
// a file fileName, where path is the path to it, and returns it.
int sizeOf(char* fileName, char* path)
{
	//VARs
	int result = 0;
	struct stat info;
	// collects information about the given file
	result = lstat(apend(fileName,path), &info);
	// if the file does not exist returns 0
	if(result != 0)
	{
		return 0;
	}
	// if the file is a directory it returns the size of
	// the directory
	if(S_ISDIR(info.st_mode) != 0)
	{
		return dirSize(fileName,path);
	}
	// if the file is not a symbolic link then it returns the
	// size of the file
	if(S_ISLNK(info.st_mode) == 0)
	{
		return info.st_size;
	}
	// if the file is a symbolic link it returns zero
	else
	{
		return 0;
	}

}

// char* apend(char* newDir, char* path) adds a new directory to the path
char* apend(char* newDir, char* path)
{
	char* newPath = malloc(strlen(path) * sizeof(char) + strlen(newDir) * sizeof(char) + 2 * sizeof(char));
	strcpy(newPath, path);
	strcat(newPath, "/");
	strcat(newPath, newDir);
	return newPath;
}
