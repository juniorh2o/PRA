#include "FileOrganizedReader.h"
#include "sale.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <ctime>
using namespace std;


FileOrganizedReader::FileOrganizedReader(int numberofObjects)
{
	this->numberofObjects = numberofObjects;
	this->saleIndexList = (int*) malloc (this->numberofObjects * sizeof(int));
	this->numPage = 1;
};

int FileOrganizedReader::openFile(){
	this->file.open("database/database.bin", std::ios::binary); 
	this->indexFile.open("database/databaseIndexed.bin", std::ios::binary); 

	return 1;
};

int FileOrganizedReader::readFile(int firstLoop){
	this->start = std::clock();
	if(!this->file){ 
		cerr << "Arquivo database.bin nao pode ser aberto." << endl; 
		return 0; 
	} 
	if(!this->indexFile){ 
		cerr << "Arquivo databaseIndexed.bin nao pode ser aberto." << endl; 
		return 0; 
	} 
	
	this->indexFile.read((char *)(this->saleIndexList),sizeof(int) * this->numberofObjects);

	int i=0;
	int curPos;
	sale* saleObject = new sale;
	for(i; i< this->numberofObjects; i++){
		curPos = this->saleIndexList[i] -1;
		this->file.seekg(curPos * sizeof(sale),ios_base::beg);
		this->file.read((char *)(saleObject),sizeof(sale));

		cout << "Cod Venda: " << saleObject->code << endl;
		cout << "Cod Customer: " << saleObject->customerCod << endl;
		cout << "Cod Seller: " << saleObject->sellerCod << endl;
		cout << "Date: " << saleObject->day << "/" << saleObject->month << "/" << saleObject->year << endl;
		cout << "Value: " << saleObject->value << endl;
		cout << "Prod 1 : " << saleObject->prod1 << endl;
		cout << "Prod 2 : " << saleObject->prod2 << endl;
		cout << "Prod 3 : " << saleObject->prod3 << endl << endl;
	}
	
	int option;
	if(firstLoop){
		do{
			this->finish = std::clock();
			cout << "Duration read: " << this->finish - this->start << " miliseconds! " << endl;
			
			cout << "1: Previous page" << endl;
			cout << "2: Next page" << endl;
			cout << "3: Exit" << endl;
			cout << "Option: ";
			cin >> option;
		
			system("cls");

			if(option == 1){
				this->numPage--;
				this->indexFile.seekg(sizeof(int) * this->numberofObjects * (this->numPage -1),ios_base::beg);
				this->readFile(0);
			}else if(option == 2){
				this->numPage++;
				this->readFile(0);
			}else
				return 1;
	
		}while (option != 3);
	}
	
	return 1;
}

int FileOrganizedReader::closeFile(){
	this->file.close();
	this->indexFile.close();
	

	delete[] this->saleIndexList;
	
	return 1;
};
