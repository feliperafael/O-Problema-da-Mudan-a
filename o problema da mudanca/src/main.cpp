#include <iostream>
#include "read.h"
#include "posto.h"
#include "caminhao.h"
#include <string>
#include <stdio.h>
#define CAPACIDADE 200  //Capacidade (l)
#define CONSUMO 1       //Consumo (km/l)
using namespace std;

/*
 * Verifica possibilidade da solução. Retorna verdadeiro se for impossível.
 */
bool impossivel(posto** postos, int numPostos, int dist){  
    //Primeiro caso: o primeiro posto eh muito longe do comeco.
    if(CAPACIDADE/2*CONSUMO < postos[0]->distancia)
        return true;

    //Segundo caso: o ultimo posto eh muito longe do destino
    if(CAPACIDADE/2*CONSUMO < dist - postos[numPostos-1]->distancia)
        return true;

    //Terceiro caso: postos forem muito distantes entre si
    for(int i = 1 ; i < numPostos ; i++){
        if(CAPACIDADE*CONSUMO < postos[i]->distancia - postos[i-1]->distancia)
            return true;
    }
    return false;
}

/*
 * Troca dois elementos de lugar no vetor
 */
void troca(posto* a, posto* b){   
    posto * aux = a;
    a = b;
    b = aux;
}

/* 
 * Auxiliar do quickSort: particiona o vetor de postos de combustivel
 */
int particionar(posto** v, int p, int n){    
    int i=p, j;
    for(j=p+1;j<n;j++)
        if(v[j]->preco<v[p]->preco){
            i++;
            swap(v[i], v[j]);
        }
    swap(v[i],v[p]);
    return i;
}

/*
 * Algoritmo de ordenação Quick Sort. Ordena os postos de combustivel com base no preco.
 */
void quickSort(posto** v, int i, int f){
    if(i<f){
        int aux = particionar(v,i,f+1);
        quickSort(v, i, aux-1);
        quickSort(v, aux+1, f);
    }
}

/*
 * Atualiza os valores do vetor de tanque de combustivel com base nos abastecimentos.
 */
void atualizaTanque(posto** postos, float* tanque, float* abastecimento, int tam){
    tanque[0] = (float) CAPACIDADE/2 - postos[0]->distancia/CONSUMO;
    for(int i=1;i<tam;i++){
        tanque[i] = (float) tanque[i-1] - (postos[i]->distancia - postos[i-1]->distancia)/CONSUMO + abastecimento[i-1];
        tanque[i] = tanque[i]<0? 0:tanque[i];
    }
    cout<<endl;
}

/*
 * Implementa a logica de construcao da solucao.
 */
void constroi(posto** postos, posto** postosOrd, float *tanque, float* abastecimento, int tam, int dist){
    int distFaltante;   //Distancia ate o final
    int posicaoAtual;   //Indice referente aa ordem dos postos na estrada
    int distPostos;     //Distancia entre dois postos

    // O algoritmo percorre todos os postos, do mais barato ao mais caro
    for(int i=0;i<tam;i++){
        distFaltante = dist - postosOrd[i]->distancia;   //Calcula a distancia faltante
        posicaoAtual = postosOrd[i]->posicao;    //Obtem a posicao do posto na estrada
        
        //Teste se eh o ultimo posto da estrada (tratamento especial)
        if(posicaoAtual == tam-1){
            //O abastecimento devera ser suficiente para eu chegar com meio tanque no final:
            abastecimento[posicaoAtual] = (float)CAPACIDADE/2 + distFaltante/CONSUMO - tanque[posicaoAtual];

            continue;   //Posso continuar o loop para o proximo posto
        }

        //Vou percorrer os proximos postos pra ver se ja tenho abastecimento agendado
        //Se eu ja agendei um abastecimento em um posto que esta por vir, eu so preciso
        // abastecer o suficiente para chegar ate ele
        for(int j=posicaoAtual+1;j<tam;j++){
            if(abastecimento[j]!=0){
                //Calculo a distancia do posto atual ate o que tem abastecimento agendado
                distPostos = postos[j]->distancia - postos[posicaoAtual]->distancia;

                //Abasteco ate chegar nesse posto
                abastecimento[posicaoAtual] = (float) distPostos/CONSUMO - tanque[posicaoAtual];

                break;  //Nao preciso percorrer o resto dos postos
            }
            else if(j == tam-1){    //Cheguei no final, nada agendado
                //Abasteco o maximo pra chegar ate o final
                abastecimento[posicaoAtual] = (float) CAPACIDADE/2 + distFaltante/CONSUMO - tanque[posicaoAtual];
            }
        }

        //Correcoes necessarias:
        //Primeiro caso: o abastecimento vai exceder a capacidade maxima do tanque
        abastecimento[posicaoAtual] = abastecimento[posicaoAtual]>CAPACIDADE? CAPACIDADE: abastecimento[posicaoAtual];
        //Segundo caso: a gasolina que eu ja tinha + abastecimento excedem a capacidade
        abastecimento[posicaoAtual] = (tanque[posicaoAtual] + abastecimento[posicaoAtual])>CAPACIDADE? CAPACIDADE-tanque[posicaoAtual]: abastecimento[posicaoAtual];
        //Terceiro caso: abastecimento negativo
        abastecimento[posicaoAtual] = abastecimento[posicaoAtual]<0? 0:abastecimento[posicaoAtual];

        //Por fim, atualiza o valor do tanque
        atualizaTanque(postos,tanque,abastecimento,tam);
    }
}

int main(){

	read * data = new read();
	posto ** postos =data->read_file("input/input_old.dat"); //Postos de gasolina são alocados dinamicamente

	
	for( int i = 0; i < data->n_postos; i++)
		postos[i]->print();
		
    //Substituir pela leitura
    int distanciaCidades = data->distancia_entre_cidades;    //Distância em km até o destino
    int numPostos = data->n_postos;      //Numero de postos de combustível no caminho
    

    //Avaliacao da impossibilidade
    if(impossivel(postos, numPostos, distanciaCidades)){
        cout<<"Impossivel"<<endl;
        return 0;
    }

    //Criacao de vetores para auxiliar nos calculos
    float* tanque = new float[numPostos];           //Estado anterior do tanque em cada um dos postos
    float* abastecimento = new float[numPostos];   //Numero de litros abastecidos em cada posto
    for(int i=0;i<numPostos;i++){   //Preenche os vetores com dados que ja sabemos
        abastecimento[i] = 0;
        if(CONSUMO*CAPACIDADE/2 - postos[i]->distancia>0)
            tanque[i] = (float) CAPACIDADE/2 - (CONSUMO*CAPACIDADE/2 - postos[i]->distancia)/CONSUMO;
        else tanque[i] = 0;
    }

    //Copia do vetor de postos para que ele seja ordenado
    posto** postosOrd = new posto*[numPostos];
    for(int i=0;i<numPostos;i++)
        postosOrd[i] = postos[i];

    //Ordenacao do vetor de postos com relacao aos precosatualizatualiz
    quickSort(postosOrd, 0, numPostos-1);

    //Chamada da contrucao
    constroi(postos, postosOrd,tanque,abastecimento, numPostos, distanciaCidades);
    float valor = 0;
    for(int i=0;i<numPostos;i++){
        cout<<postos[i]->distancia<<" km:"<<endl;
        cout<<"Abasteceu "<<abastecimento[i]<<" litros no posto "<<i<<" a "<<postos[i]->preco<<" reais."<<endl;
        cout<<"O tanque ficou com "<<tanque[i] + abastecimento[i]<<" litros."<<endl;
        valor += abastecimento[i]*postos[i]->preco;
        cout<<endl;
    }
    cout<<"Valor total: "<<valor<<endl;


    return 0;
}
