#ifndef ARVOREVP_H_INCLUDED
#define ARVOREVP_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include "ProductReview.h"

using namespace std;

enum Cor {VERMELHO, PRETO};

struct No{
    ProductReview* review;
    string id;
    Cor cor;
    No *esq, *dir, *pai;

    No(ProductReview* review) : review(review){
        esq = dir = pai = NULL;
        cor = VERMELHO;
        id = review->getUserId() + review->getProductId();
    }
};

struct Metricas {
    double comparacoes = 0;
    double tempo = 0.0000000;

};

class ArvoreVP{
    private:
        No *raiz; 
        Metricas metricas;
        void atualizarMetricas(double comparacoes);
    
    protected:
        void rotacaoEsquerda(No *&, No *&, int &comparacoes);
        void rotacaoDireita(No *&, No *&, int &comparacoes);
        void balancearInsercao(No *&, No *&, int &comparacoes);
    public:
        ArvoreVP() : raiz(NULL){};
        void insere(ProductReview *pr);
        ProductReview* busca(string userId, string productId);
        void print();
        int getComparacoes();
};

#endif