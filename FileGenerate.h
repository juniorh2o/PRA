#ifndef FILEGENERATE_H
#define FILEGENERATE_H
#include <iostream>
#include <fstream>
#include <ctime>

#include "sale.h"
using namespace std;

/**
 * @brief Classe geradora de arquivo
 * Gera o arquivo com o tamanho estipulado nos parâmentros. salva os dados em blocos.
 */
class FileGenerate
{
public:
	operator char*();

	FileGenerate(int maxsize, int blocksize);

	int openFile();
	int createBlock();
	int saveData();
	int closeFile();
	int readFile();

	ofstream file;

	int maxsize;
	int blocksize;
	int numberofObjects;
	int accessCounter;
	sale* saleList;

	std::clock_t start;
	std::clock_t finish;
};

#endif