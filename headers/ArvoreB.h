#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include <iostream>
#include <algorithm>
#include "ProductReview.h"

const int NO_MAX_KEYS = 20;


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
        void insereNaoCheio(ProductReview* k, int &comp);
        void divideFilho(int i, NoArvoreB* y);
        void imprime();
        
friend class ArvoreB;
//acessar os attributos privado dessa classe

};

class ArvoreB
{
    friend class NoArvoreB;
    NoArvoreB *raiz;
    int t; // grau minimo
    int comp;
    public:
        ArvoreB(){ raiz = NULL; this->t = NO_MAX_KEYS; this->comp = 0;}
        

        void print()
        {
            if (raiz != NULL) raiz->imprime();
        }

        NoArvoreB* auxBusca(string userId, string productId);

        ProductReview* busca(string userId, string productId);

        void insere(ProductReview* k);

        void setT(int t){this->t = t;};

        int getComparacoes(){
            return this->comp;
        }

        void aumentaComparacao(int comp){
            this->comp += comp;
        }

};




#endif