#include "read.h"

read::read()

{
}



posto ** read::read_file(string input){
	ifstream file;
	file.open(input);
	
	file >> distancia_entre_cidades;
	file >> n_postos;
	
	posto ** postos = new posto*[n_postos];
	posto * p;
	
	for ( int i = 0; i < n_postos; i++ ){
		p = new posto();
		file >> p->distancia;
		file >> p->preco;
		p->posicao = i;
		postos[i] = p;
	}
	file.close();
	return postos;
}


read::~read()
{
    //dtor
}
