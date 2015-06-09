#include "FileReader.h"
#include "sale.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <ctime>
using namespace std;


FileReader::FileReader(int numberofObjects)
{
	this->numberofObjects = numberofObjects;
	this->saleList = (sale*) malloc (this->numberofObjects * sizeof(sale));
	this->numPage = 1;
};

int FileReader::openFile(int option){
	if(option== 0)
		this->file.open("database/database.bin", std::ios::binary); 
	else
		this->file.open("database/databaseOrdenated.bin", std::ios::binary);

	return 1;
};

int FileReader::readFile(int firstLoop){	
	this->start = std::clock();
	if(!this->file){ 
		cerr << "Arquivo nao pode ser aberto." << endl; 
		return 0; 
	} 
	
	this->file.read((char *)(this->saleList),sizeof(sale) * this->numberofObjects);
	
	int i=0;
	for(i; i< this->numberofObjects; i++){
		cout << "Cod Venda: " << this->saleList[i].code << endl;
		cout << "Cod Customer: " << this->saleList[i].customerCod << endl;
		cout << "Cod Seller: " << this->saleList[i].sellerCod << endl;
		cout << "Date: " << this->saleList[i].day << "/" << this->saleList[i].month << "/" << this->saleList[i].year << endl;
		cout << "Value: " << this->saleList[i].value << endl;
		cout << "Prod 1 : " << this->saleList[i].prod1 << endl;
		cout << "Prod 2 : " << this->saleList[i].prod2 << endl;
		cout << "Prod 3 : " << this->saleList[i].prod3 << endl << endl;
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
				this->file.seekg( sizeof(sale) * this->numberofObjects * (this->numPage -1),ios_base::beg);
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

int FileReader::closeFile(){
	this->file.close();

	delete[] this->saleList;

	return 1;
};
