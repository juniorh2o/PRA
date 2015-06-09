#ifndef FILEREADER_H
#define FILEREADER_H
#include <iostream>
#include <fstream>
#include <ctime>

#include "sale.h"
using namespace std;

class FileReader
{
public:
	operator char*();

	FileReader(int blocksize);
	int openFile(int option);
	int closeFile();
	int readFile(int firstloop);
	
	int numberofObjects;
	int numPage;

	ifstream file;

	sale* saleList;

	std::clock_t start;
	std::clock_t finish;
};

#endif
