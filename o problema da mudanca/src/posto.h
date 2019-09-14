#ifndef POSTO_H
#define POSTO_H
#include <iostream>

using namespace std;
class posto
{
    public:
    	int distancia;  //Distancia entre o ponto de partida e o posto
		float preco;    //Valor do litro de gasolina no posto
		int posicao;    //Posicao ordenada do posto no caminho
        /** Default constructor */
        posto();
        
        void print();
        /** Default destructor */
        virtual ~posto();

    protected:

    private:
};

#endif // POSTO_H
