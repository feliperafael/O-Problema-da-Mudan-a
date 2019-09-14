#include "posto.h"

#include <iostream>

using namespace std;

posto::posto()
{
    //ctor
}
      
void posto::print(){
	cout << "posto " << posicao << "\npreco combustivel: R$ " << preco << "\ndistancia: " << distancia << " km" << endl; 
}

posto::~posto()
{
    //dtor
}
