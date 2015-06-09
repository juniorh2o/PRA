/*
Tema 4 - Vendas: listagem de vendas de uma loja: codigo do cliente,
codigo do vendedor, data da venda (dd/mm/aaaa), valor da venda (R$),
listagem dos itens comprados (qtde. indeterminada);
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "FileGenerate.h"
#include "FileOrganizer.h"
#include "FileReader.h"
#include "FileOrganizedReader.h"

//Dados em bytes
//1024 = 1Kb
//1024000 = 1Mb
//1024000000 = 1Gb

using namespace std;
int  maxsize;
int blocksize;
int numberofObjects;
int option, perloop, loopamount;

void generateFile(){
	cout << "File  size: ";
	cin >> maxsize;
	cout << "Block size: ";
	cin >> blocksize;
	cout << "Processing..." << endl;
	FileGenerate* generator = new FileGenerate(maxsize, blocksize);
	int size = 0;

	generator->openFile();

	while(size < generator->maxsize){
		generator->createBlock();
		generator->saveData();
		size += generator->blocksize;
	}
	generator->closeFile(); 
	
	delete generator;
}

void readFile(){
	cout << "Registers number: ";
	cin >> numberofObjects;

	cout << "Processing..." << endl << endl;
	FileReader* reader = new FileReader(numberofObjects);
	reader->openFile(0);
	reader->readFile(1);
	reader->closeFile();
	delete reader;
}

void organizeFile(){
	cout << "Order by " << endl;
	cout << "1: Customer" << endl;
	cout << "2: Seller" << endl;
	cout << "Option: ";
	cin >> option;

	cout << "Registers per loop: ";
	cin >> perloop;

	cout << "Loops amount: ";
	cin >> loopamount;
	
	cout << "Processing..." << endl << endl;
	FileOrganizer* organizer = new FileOrganizer(option, perloop, loopamount);
	organizer->openFiles();

	organizer->generateFileToOrganize();
	
	int i = 0;
	organizer->organize();
	
	organizer->generateIndexFile();
	organizer->closeFiles();
	delete organizer;
}

void readOrdenatedFile(){
	cout << "Registers number: ";
	cin >> numberofObjects;

	cout << "Processing..." << endl << endl;
	FileReader* reader = new FileReader(numberofObjects);
	reader->openFile(1);
	reader->readFile(1);
	reader->closeFile();
	delete reader;
}

void readIndexedFile(){
	cout << "Registers number: ";
	cin >> numberofObjects;

	cout << "Processing..." << endl << endl;
	FileOrganizedReader* reader = new FileOrganizedReader(numberofObjects);
	reader->openFile();
	reader->readFile(1);
	reader->closeFile();
	delete reader;
}

int main() {
	int option = 0;
	do{
		cout << "1: Generate file" << endl;
		cout << "2: Read file" << endl;
		cout << "3: Ordenate file" << endl;
		cout << "4: Read Ordenated file" << endl;
		cout << "5: Read Indexed file" << endl;
		cout << "6: Exit" << endl;
		cout << "Option: ";
		cin >> option;
		
		if(option == 1)
			generateFile();
		else if(option == 2)
			readFile();
		else if(option == 3)
			organizeFile();
		else if(option == 4)
			readOrdenatedFile();
		else if(option == 5)
			readIndexedFile();
		else if(option == 6)
			return 1;
		else
			system("cls");
	
	}while (option != 6);
	
	return 1;
}
