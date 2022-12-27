#ifndef ARVOREVP_H_INCLUDED
#define ARVOREVP_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include "ProductReview.h"

using namespace std;

enum Cor {VERMELHO, PRETO};

struct No{
    ProductReview review;
    string id;
    Cor cor;
    No *esq, *dir, *pai;

    No(ProductReview review) : review(review){
        esq = dir = pai = NULL;
        cor = VERMELHO;
        id = review.getUserId() + review.getProductId();
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