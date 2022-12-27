#ifndef ARVOREVP_H_INCLUDED
#define ARVOREVP_H_INCLUDED

#include <iostream>
#include <cstdlib>

using namespace std;

enum Cor {VERMELHO, PRETO};

struct No{
    int data;
    Cor cor;
    No *esq, *dir, *pai;

    No(int data) : data(data){
        esq = dir = pai = NULL;
        cor = VERMELHO;
    }
};

class ArvoreVP{
    private:
        No *raiz; 
    
    protected:
        void rotacaoEsquerda(No *&, No *&);
        void rotacaoDireita(No *&, No *&);
        void balancearInsercao(No *&, No *&);
    public:
        ArvoreVP() : raiz(NULL){}
        void inserir(int data);
        void imprimir();
        No* buscar(int data);
};


#endif