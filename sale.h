#ifndef SALE_H
#define SALE_H
#include <string>

class sale
{
public:
	sale();
	int generateYear();
	int generateMonth();
	int generateDay();
	int populate();

	int code;
	int customerCod;
	int sellerCod;
	int day;
	int month;
	int year;
	float value;
	char* prod1;
	char* prod2;
	char* prod3;
};
#endif
