#include "FileGenerate.h"
#include "sale.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <ctime>
using namespace std;

/**
 * @brief Arquivo para interagir com a classe
 * @param int maxsise inteiro com o tamanho que o arquivo terá
 * @param int blocksize inteiro com o tamanho do bloco a ser salvo
 */
FileGenerate::FileGenerate(int maxsize, int blocksize)
{
	this->maxsize = maxsize;
	this->blocksize = blocksize;
	this->numberofObjects = this->blocksize / sizeof(sale);
	this->accessCounter = 0;
	this->saleList = (sale*) malloc (this->numberofObjects * sizeof(sale));
};

/** Método responsável por abrir o arquivo
 */
int FileGenerate::openFile(){
	this->file.open("database/database.bin",std::ios::binary);
	
	this->start = std::clock();

	return 1;
};

/** Método responsável por criar o bloco de registro
 */
int FileGenerate::createBlock(){
	for(int x=0;x < this->numberofObjects;x++){
		sale newSale;
		this->saleList[x] = newSale;
		this->saleList[x].populate();
	}
	return 1;
};


/** Método responsável por salvar os registros no arquivo criado
 */
int FileGenerate::saveData(){
	this->file.write(reinterpret_cast<char *>(this->saleList),sizeof(sale) * this->numberofObjects);
	this->accessCounter++;

	return 1;
};


/** Método responsável fechar o arquivo
 */
int FileGenerate::closeFile(){
	this->file.close();
	this->finish = std::clock();

	delete[] this->saleList;


	cout << "Disk access counter: " << this->accessCounter << endl;
	cout << "Duration: " << this->finish - this->start << " miliseconds! " << endl;
	return 1;
};
