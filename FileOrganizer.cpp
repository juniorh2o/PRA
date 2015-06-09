#include "FileOrganizer.h"
#include "sale.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <ctime>
#include <stack>
#include <queue>

using namespace std;

stack<sale>* MINCUSTOMER(stack<sale>* X, stack<sale>* Y ){
	if(X == NULL || X->empty())
		if(Y == NULL || Y->empty())
			return NULL;
		else
			return Y;
	else
		if(Y == NULL || Y->empty())
			return X;
	else{
		if(X->top().customerCod < Y->top().customerCod)
			return X;
		else
			return Y;
	}
};

stack<sale>* MINSELLER(stack<sale>* X, stack<sale>* Y ){
	if(X == NULL || X->empty())
		if(Y == NULL || Y->empty())
			return NULL;
		else
			return Y;
	else
		if(Y == NULL || Y->empty())
			return X;
	else{
		if(X->top().sellerCod < Y->top().sellerCod)
			return X;
		else
			return Y;
	}
};

/* Adapted from https://sites.google.com/site/spaceofjameschen/home/stack/sort-a-stack */
void FileOrganizer::sortStack(stack<sale> &s)
{
    sale v, min;
    stack<sale> t;

    while(!s.empty()){
        v = s.top();
        s.pop();

        t.push(v);
    }

    while(!t.empty()){
        min = t.top();
        t.pop();

		if(this->option == 1){
			while(!s.empty() && s.top().customerCod < min.customerCod){
				v = s.top();
				s.pop();

				t.push(v);
			}
		} 
		else if(this->option == 2){
			while(!s.empty() && s.top().sellerCod < min.sellerCod){
				v = s.top();
				s.pop();

				t.push(v);
			}
		}
        s.push(min);
    }
};

FileOrganizer::FileOrganizer(int option, int perloop, int loopamount)
{
	this->stackList = new stack<sale>[8];
	this->regNumber = perloop;
	this->option = option;
	this->loopAmount = loopamount;
};

int FileOrganizer::openFiles(){ 
	this->start = std::clock();

	this->fileRead.open("database/database.bin", std::ios::binary);	
	this->fileOrganized.open("database/databaseOrdenated.bin",std::ios::in | std::ios::out |std::ios::trunc |std::ios::binary);
	this->fileIndexWrite.open("database/databaseIndexed.bin",std::ios::binary);

	this->fileRead.seekg (0, ios::end);
	
	this->numberofObjects = this->fileRead.tellg() / sizeof(sale);

	this->fileRead.seekg (0, ios::beg);

	this->saleList = (sale*) malloc (this->regNumber * sizeof(sale));
	this->ordenatedSale = (sale*) malloc (this->regNumber * sizeof(sale));
	this->ordenatedIndex = (int*) malloc (this->regNumber * sizeof(int));

	return 1;
};

int FileOrganizer::generateFileToOrganize(){
	this->loopObjectCount = 0;
	int amountOfObjects = this->numberofObjects;
	
	while(amountOfObjects != 0){
		if(amountOfObjects >= this->regNumber){
			this->loopObjectCount = this->regNumber;
			amountOfObjects -= this->regNumber;
		}
		else{
			this->loopObjectCount = amountOfObjects;
			amountOfObjects = 0;
		}

		this->fileRead.read((char *)(this->saleList),sizeof(sale) * this->loopObjectCount);

		this->fileOrganized.write(reinterpret_cast<char *>(this->saleList),sizeof(sale) * this->loopObjectCount);
	}

	return 1;
}

int FileOrganizer::stackOrganize(){
	//Criar e preencher as 8 pilhas
		int i=0;
		int j;

		int objectsPerStack = this->loopObjectCount / 8;
			
		for(i; i< 8; i++){
			std::stack<sale> newStack;
			this->stackList[i] = newStack;
			
			j=0;
			for(j; j<objectsPerStack ; j++){
				this->stackList[i].push(this->saleList[j+objectsPerStack*i]);
			}
			//Ordenar a pilha
			this->sortStack(this->stackList[i]);
		}
		
		//Intercalar as 8 pilhas em um array
		stack<sale>* winner;
		while(
		!this->stackList[0].empty() ||
		!this->stackList[1].empty() ||
		!this->stackList[2].empty() ||
		!this->stackList[3].empty() ||
		!this->stackList[4].empty() ||
		!this->stackList[5].empty() ||
		!this->stackList[6].empty() ||
		!this->stackList[7].empty()
			){
			if(this->option == 1)
				winner = MINCUSTOMER( 
							MINCUSTOMER( 
								MINCUSTOMER( &this->stackList[0], &this->stackList[1] ),
								MINCUSTOMER( &this->stackList[2], &this->stackList[3] ) 
							),
							MINCUSTOMER( 
								MINCUSTOMER( &this->stackList[4], &this->stackList[5] ),
								MINCUSTOMER( &this->stackList[6], &this->stackList[7] )
							)
						 );
			else if(this->option == 2)
				winner = MINSELLER(
							MINSELLER(
								MINSELLER( &this->stackList[0], &this->stackList[1] ),
								MINSELLER( &this->stackList[2], &this->stackList[3])
							),
							MINSELLER(
								MINSELLER( &this->stackList[4], &this->stackList[5] ),
								MINSELLER( &this->stackList[6], &this->stackList[7] )
							)
						 );

			if(winner != NULL){
				this->queueSale.push(winner->top());
				winner->pop();
			}
		}

		i = 0;
		while(!this->queueSale.empty()){
			this->ordenatedSale[i] = this->queueSale.front();
			this->queueSale.pop();
			i++;
		}

		return 1;
};

int FileOrganizer::organize(){
	int i;
	for(i=0;i<this->loopAmount;i++){

		this->fileOrganized.seekg (0, ios::beg);
		this->fileOrganized.seekp (0, ios::beg);

		this->loopObjectCount = 0;
		int amountOfObjects = this->numberofObjects;
	
		int totalLoops = 0;

		while(amountOfObjects != 0){

			if(amountOfObjects > this->regNumber){
				this->loopObjectCount = this->regNumber;
				amountOfObjects -= this->regNumber;
			}
			else{
				this->loopObjectCount = amountOfObjects;
				amountOfObjects = 0;
			}

			//Ler X registros
			this->fileOrganized.readsome((char *)(this->saleList),sizeof(sale) * this->loopObjectCount);

			this->stackOrganize();
	
			this->fileOrganized.write(reinterpret_cast<char *>(this->ordenatedSale),sizeof(sale) * this->loopObjectCount);
	
			if(amountOfObjects != 0){
				this->fileOrganized.seekg(sizeof(sale) * (totalLoops * this->loopObjectCount / 2 + this->loopObjectCount/2), ios::beg);
				this->fileOrganized.seekp(sizeof(sale) * (totalLoops * this->loopObjectCount / 2 + this->loopObjectCount/2), ios::beg);
				amountOfObjects += this->loopObjectCount/2;
			}

			totalLoops++;
		}
	}
	this->fileOrganized.flush();
	return 1;
};

int FileOrganizer::generateIndexFile(){
	this->fileOrganized.seekg (0, ios::beg);
	
	int i;
	this->loopObjectCount = 0;
	int amountOfObjects = this->numberofObjects;
	
	while(amountOfObjects != 0){

		if(amountOfObjects >= this->regNumber){
			this->loopObjectCount = this->regNumber;
			amountOfObjects -= this->regNumber;
		}
		else{
			this->loopObjectCount = amountOfObjects;
			amountOfObjects = 0;
		}

		//Ler X registros
		this->fileOrganized.readsome((char *)(this->ordenatedSale),sizeof(sale) * this->loopObjectCount);
		i=0;
		for(i; i< this->loopObjectCount; i++){
			this->ordenatedIndex[i] = this->ordenatedSale[i].code;
		}

		this->fileIndexWrite.write(reinterpret_cast<char *>(this->ordenatedIndex),sizeof(int) * this->loopObjectCount);
	}

	return 1;
}

int FileOrganizer::closeFiles(){
	this->fileRead.close();
	this->fileIndexWrite.close();
	this->fileOrganized.close();

	delete[] this->saleList;
	delete[] this->ordenatedSale;
	delete[] this->ordenatedIndex;

	this->finish = std::clock();
	cout << "Duration: " << this->finish - this->start << " miliseconds! " << endl;
	return 1;
};
