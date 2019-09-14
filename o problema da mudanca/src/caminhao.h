#ifndef CAMINHAO_H
#define CAMINHAO_H
#include <iostream>

using namespace std;
class caminhao
{
    public:
		int capacidade;    //capacidade do tanque
		int tanque;    //tanque atual
        /** Default constructor */
        caminhao();
        
        void print();
        /** Default destructor */
        virtual ~caminhao();

    protected:

    private:
};

#endif // CAMINHAO_H
