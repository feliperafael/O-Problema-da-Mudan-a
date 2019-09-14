#ifndef READ_H
#define READ_H

#include <string>
#include <fstream>
#include "posto.h"

using namespace std;


class read
{
    public:
    	int distancia_entre_cidades;
    	int n_postos;
        /** Default constructor */
        read();
        posto ** read_file(string input);
       
        /** Default destructor */
        virtual ~read();

    protected:

    private:
};

#endif // READ_H
