#ifndef FILEORGANIZEDREADER_H
#define FILEORGANIZEDREADER_H
#include <iostream>
#include <fstream>
#include <ctime>

#include "sale.h"
using namespace std;

class FileOrganizedReader
{
public:
	operator char*();

	FileOrganizedReader(int blocksize);
	int openFile();
	int closeFile();
	int readFile(int firstloop);
	
	int numberofObjects;
	int numPage;

	ifstream file;
	ifstream indexFile;

	int* saleIndexList;

	std::clock_t start;
	std::clock_t finish;
};

#endif
