#include "caminhao.h"

caminhao::caminhao()
{
    //ctor
}
      
void caminhao::print(){
	cout << "caminhao " << tanque << "/" << capacidade << " L" << endl; 
}

caminhao::~caminhao()
{
    //dtor
}
