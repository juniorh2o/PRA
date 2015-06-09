#ifndef FILEORGANIZER_H
#define FILEORGANIZER_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <stack>
#include <queue>

#include "sale.h"
using namespace std;

class FileOrganizer
{
public:
	operator char*();

	FileOrganizer(int option, int perloop, int loopamount);

	int regNumber;

	int openFiles();
	int generateFileToOrganize();
	int stackOrganize();
	int organize();
	int generateIndexFile();
	int closeFiles();

	void sortStack(stack<sale> &s);

	sale* saleList;

	sale* ordenatedSale;

	int* ordenatedIndex;

	int loopObjectCount;

	int loopAmount;

	stack<sale>* stackList;

	queue<sale> queueSale;

	int numberofObjects;

	int option;

	ofstream fileIndexWrite;
	ifstream fileRead;
	fstream fileOrganized;


	std::clock_t start;
	std::clock_t finish;
};

#endif