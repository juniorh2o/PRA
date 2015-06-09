#include "sale.h"
#include <stdlib.h>
#include <stdio.h>

char* prodList[] = {"Água sanitária","Álcool","Alvejante","Amaciante","Anil","Cera em pasta","Cera líquida","Desentupidor de pia","Desinfetante banheiro","Desinfetante geral","Desodorizador (banheiro)","Desodorizador (casa)","Detergente","Eliminador de odores (geladeira)","Eliminador de odores (roupas)","Esponja de aço","Esponja dupla face","Flanela de limpeza","Graxa","Guardanapo de papel","Inseticida e raticida","Lã de aço","Limpador","Limpador de tapetes","Limpa-forno","Limpa-vidros","Lustra-móveis","Luva doméstica","Pano de limpeza de cozinha","Passa-roupas","Polidor de metais","Pré-lavagem","Removedor","Rodo","Rodo de pia","Sabão de coco","Sabão em barra","Sabão em pó","Sabão líquido (roupas)","Saco de lixo grande","Saco de lixo médio","Saco de lixo pequeno","Saponáceo","Tira-manchas","Toalha de papel","Vassoura","Absorvente higiênico","Algodão","Anti-séptico bucal","Condicionador","Cotonetes","Creme de barbear","Creme hidratante para as mãos","Creme hidratante para o corpo","Creme para pentear","Desodorante","Escova de cabelos","Escova de dentes","Esmalte","Esponja de banho","Fio dental","Fralda descartável","Lâminas de barbear","Lenços umedecidos","Lixa de unhas","Loção contra assaduras","Loção de limpeza","Papel higiênico","Pasta de dentes","Pente","Protetor solar","Removedor de esmaltes","Sabonete em barra","Sabonete líquido","Talco infantil","Xampu","Carne bovina","Carne suína","Coalhada","Cream cheese","Creme de leite fresco","Frango","Iogurte","Leite","Linguiça","Patê","Peixe","Presunto","Queijo","Requeijão cremoso","Salsicha","Água","Aperitivos e licores","Cerveja","Chás prontos","Destilados","Isotônicos e energéticos","Outros","Refesco em pó","Refrigerantes","Sucos","Vinho","Empanados","Hambúrguer","Legumes","Pizza","Pratos prontos","Salgadinhos","Sobremesa","Sorvete","Abacate","Acerola","Ameixa","Amora","Banana","Cereja","Figo","Framboesa","Laranja","Limão","Maçã","Mamão","Manga","Melancia","Melão","Morango","Nectarina","Pera","Pêssego","Pitanga","Uva","Acelga","Agrião","Alecrim","Alface","Alho","Batata","Batata doce","Cebola","Chuchu","Cogumelo","Espinafre","Hortelã","Inhame","Mandioca","Manjericão","Orégano","Pepino","Pimenta","Pimentão","Quiabo","Repolho","Rúcula","Salsinha e cebolinha","Tomate","Vagem","Adoçante","Biscoito doce","Biscoito salgado","Bolo","Café","Cereal matinal","Chá","Chocolate em pó","Filtro de papel","Leite em pó","Mistura para bolo","Pão de forma","Pão francês","Torradas","Açúcar","Alimento infantil","Amido de milho","Arroz","Aspargo em conserva","Atum em lata","Aveia","Azeite","Azeitonas","Batata frita","Caldo de carne/galinha/peixe","Catchup","Chocolate","Creme de leite em lata","Ervilha","Ervilha em conserva","Farinha de milho","Farinha de rosca","Farinha de trigo","Feijão","Gelatina","Gelatina em pó","Grão-de-bico","Leite condensado","Lentilha","Macarrão","Macarrão massa fresca","Macarrão para sopa","Maionese","Milho em conserva","Milho para pipoca","Molho de soja","Molho de tomate","Mostarda","Óleo","Ovos","Sal","Salgadinhos","Sardinha em lata"};
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
