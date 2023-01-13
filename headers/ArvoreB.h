#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include <iostream>
#include <algorithm>
#include "ProductReview.h"

const int NO_MAX_KEYS = 4;

class NoArvoreB
{
    ProductReview* keys;
    int t; // define grau minimo da arovre
    NoArvoreB **filho; //array de ponteiros para filho
    int n; //numero de chaves
    bool folha;

    public:
        NoArvoreB(int t, bool folha);
        ~NoArvoreB();
        void insereNaoCheio(ProductReview* k);
        void divideFilho(int i, NoArvoreB* y);
        void imprime();
        
friend class ArvoreB;
//acessar os attributos privado dessa classe

};


class ArvoreB
{
    NoArvoreB *raiz;
    int t; // grau minimo

    public:
        ArvoreB(){ raiz = NULL; this->t = NO_MAX_KEYS;}
        

        void print()
        {
            if (raiz != NULL) raiz->imprime();
        }

        NoArvoreB* auxBusca(string userId, string productId);

        ProductReview* busca(string userId, string productId);

        void insere(ProductReview* k);
};





#endif