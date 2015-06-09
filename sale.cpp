#include "sale.h"
#include <stdlib.h>
#include <stdio.h>

char* prodList[] = {"�gua sanit�ria","�lcool","Alvejante","Amaciante","Anil","Cera em pasta","Cera l�quida","Desentupidor de pia","Desinfetante banheiro","Desinfetante geral","Desodorizador (banheiro)","Desodorizador (casa)","Detergente","Eliminador de odores (geladeira)","Eliminador de odores (roupas)","Esponja de a�o","Esponja dupla face","Flanela de limpeza","Graxa","Guardanapo de papel","Inseticida e raticida","L� de a�o","Limpador","Limpador de tapetes","Limpa-forno","Limpa-vidros","Lustra-m�veis","Luva dom�stica","Pano de limpeza de cozinha","Passa-roupas","Polidor de metais","Pr�-lavagem","Removedor","Rodo","Rodo de pia","Sab�o de coco","Sab�o em barra","Sab�o em p�","Sab�o l�quido (roupas)","Saco de lixo grande","Saco de lixo m�dio","Saco de lixo pequeno","Sapon�ceo","Tira-manchas","Toalha de papel","Vassoura","Absorvente higi�nico","Algod�o","Anti-s�ptico bucal","Condicionador","Cotonetes","Creme de barbear","Creme hidratante para as m�os","Creme hidratante para o corpo","Creme para pentear","Desodorante","Escova de cabelos","Escova de dentes","Esmalte","Esponja de banho","Fio dental","Fralda descart�vel","L�minas de barbear","Len�os umedecidos","Lixa de unhas","Lo��o contra assaduras","Lo��o de limpeza","Papel higi�nico","Pasta de dentes","Pente","Protetor solar","Removedor de esmaltes","Sabonete em barra","Sabonete l�quido","Talco infantil","Xampu","Carne bovina","Carne su�na","Coalhada","Cream cheese","Creme de leite fresco","Frango","Iogurte","Leite","Lingui�a","Pat�","Peixe","Presunto","Queijo","Requeij�o cremoso","Salsicha","�gua","Aperitivos e licores","Cerveja","Ch�s prontos","Destilados","Isot�nicos e energ�ticos","Outros","Refesco em p�","Refrigerantes","Sucos","Vinho","Empanados","Hamb�rguer","Legumes","Pizza","Pratos prontos","Salgadinhos","Sobremesa","Sorvete","Abacate","Acerola","Ameixa","Amora","Banana","Cereja","Figo","Framboesa","Laranja","Lim�o","Ma��","Mam�o","Manga","Melancia","Mel�o","Morango","Nectarina","Pera","P�ssego","Pitanga","Uva","Acelga","Agri�o","Alecrim","Alface","Alho","Batata","Batata doce","Cebola","Chuchu","Cogumelo","Espinafre","Hortel�","Inhame","Mandioca","Manjeric�o","Or�gano","Pepino","Pimenta","Piment�o","Quiabo","Repolho","R�cula","Salsinha e cebolinha","Tomate","Vagem","Ado�ante","Biscoito doce","Biscoito salgado","Bolo","Caf�","Cereal matinal","Ch�","Chocolate em p�","Filtro de papel","Leite em p�","Mistura para bolo","P�o de forma","P�o franc�s","Torradas","A��car","Alimento infantil","Amido de milho","Arroz","Aspargo em conserva","Atum em lata","Aveia","Azeite","Azeitonas","Batata frita","Caldo de carne/galinha/peixe","Catchup","Chocolate","Creme de leite em lata","Ervilha","Ervilha em conserva","Farinha de milho","Farinha de rosca","Farinha de trigo","Feij�o","Gelatina","Gelatina em p�","Gr�o-de-bico","Leite condensado","Lentilha","Macarr�o","Macarr�o massa fresca","Macarr�o para sopa","Maionese","Milho em conserva","Milho para pipoca","Molho de soja","Molho de tomate","Mostarda","�leo","Ovos","Sal","Salgadinhos","Sardinha em lata"};
int currentCod=0;

sale::sale(void)
{
}

int sale::populate(){
	this->code = currentCod+1;
	currentCod++;
	this->customerCod=1 +rand()% (int)(5000 - 2);
	this->sellerCod= 1 + rand()% (int)(5000 - 2);
	this->year=this->generateYear();
	this->month=this->generateMonth();
	this->day=this->generateDay();
	this->value= static_cast <float> ( 1 + rand()% (int)(5000 - 2) );
	this->prod1= prodList[1 + rand()% (int)(209 - 1)];
	this->prod2= prodList[1 + rand()% (int)(209 - 1)];
	this->prod3= prodList[1 + rand()% (int)(209 - 1)];
	return 1;
}


int sale::generateYear(){
	return 1900 + rand()% (int)(2014 - 1901);
}

int sale::generateMonth(){
	return 1+ rand()% (int)(12 - 2);
}

int sale::generateDay(){
	int max;
	if(this->month == 2)
		max = 28;
	else if(this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 || this->month == 8 || this->month == 10 || this->month == 12)
		max = 31;
	else
		max = 30;
	return 1 + rand()% (int)(max - 2);
}
