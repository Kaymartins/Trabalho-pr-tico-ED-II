#include "../headers/RegistroHash.h"
#include "../headers/ArvoreVP.h"
#include <chrono>

using namespace chrono;

void ArvoreVP::rotacaoEsquerda(No *&raiz, No *&no, int &comparacoes){

    No *noDir = no->dir;
    no->dir = noDir->esq;

    comparacoes++;
    if(no->dir != NULL)
        no->dir->pai = no;

    noDir->pai = no->pai;

    comparacoes++;
    if(no->pai == NULL)
        raiz = noDir;

    else if(no == no->pai->esq)
        no->pai->esq = noDir;

    else
        no->pai->dir = noDir;

    noDir->esq = no;
    no->pai = noDir;

}

void ArvoreVP::rotacaoDireita(No *&raiz, No *&no, int &comparacoes){
    
    No *noEsq = no->esq;
    no->esq = noEsq->dir;

    comparacoes++;
    if(no->esq != NULL)
        no->esq->pai = no;

    noEsq->pai = no->pai;

    comparacoes++;
    if(no->pai == NULL)
        raiz = noEsq;

    else if(no == no->pai->dir)
        no->pai->dir = noEsq;

    else
        no->pai->esq = noEsq;

    noEsq->dir = no;
    no->pai = noEsq;
}

void ArvoreVP::balancearInsercao(No *&raiz, No *&no, int &comparacoes){

    No *pai = NULL;
    No *avo = NULL;

    while((no != raiz) && (no->cor != PRETO) && (no->pai->cor == VERMELHO)){
        pai = no->pai;
        avo = no->pai->pai;
        comparacoes++;
        if(pai == avo->esq){
            No *tio = avo->dir;
            
            comparacoes++;
            if(tio != NULL && tio->cor == VERMELHO){
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                no = avo;
            }

            else{
                if(no == pai->dir){
                    rotacaoEsquerda(raiz, pai, comparacoes);
                    pai = no->pai;
                }
                rotacaoDireita(raiz, avo, comparacoes);
                swap(pai->cor, avo->cor);
                no = pai;
            }
        }

        else{
            No *tio = avo->esq;

            comparacoes++;
            if((tio != NULL) && (tio->cor == VERMELHO)){
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                no = avo;
            }

            else{

                comparacoes++;

                if(no == pai->esq){
                    rotacaoDireita(raiz, pai, comparacoes);
                    no = pai;
                    pai = no->pai;
                }
                rotacaoEsquerda(raiz, avo, comparacoes);
                swap(pai->cor, avo->cor);
                no = pai;
            }
        }
    }

    raiz->cor = PRETO;
}

No* ABBInsert(No* raiz, No* no, int &comparacoes){
    /*se a arvore é vazia retorna um novo nó*/
    comparacoes++;
    if(raiz == NULL)
        return no;

    /*senão, percorre a arvore*/
    comparacoes++;
    if(no->id < raiz->id){
        raiz->esq = ABBInsert(raiz->esq, no, comparacoes);
        raiz->esq->pai = raiz;
    }

    else if(no->id > raiz->id){

        raiz->dir = ABBInsert(raiz->dir, no, comparacoes);
        raiz->dir->pai = raiz;
    }



    /*retorna a raiz (sem alterações)*/
    return raiz;

}

void ArvoreVP::insere(ProductReview* pr){
    high_resolution_clock::time_point start = high_resolution_clock::now();
    int *comparacoes = new int;
    double *tempo = new double;
    *comparacoes = 0;
    *tempo = 0;
    No *novo = new No(pr);
    
    raiz = ABBInsert(raiz, novo, *comparacoes);

    balancearInsercao(raiz, novo, *comparacoes); 
    high_resolution_clock::time_point end = high_resolution_clock::now();
    *tempo += duration_cast<std::chrono::duration<double>>(end - start).count();
    atualizarMetricas(*comparacoes);
}



// A recursive function to do inorder traversal
void imprimirAux(No *raiz)
{
    if (raiz == NULL)
        return;

    imprimirAux(raiz->esq);
    cout << raiz->id << "  " << endl;
    imprimirAux(raiz->dir);
}

void ArvoreVP::print(){
    imprimirAux(raiz);
}

ProductReview* ArvoreVP::busca(string userId, string productId){
    high_resolution_clock::time_point start = high_resolution_clock::now();
    string idBuscado = userId + productId;
    int comparacoes = 0;
    No *aux = raiz;
    
    while(aux != NULL){
        comparacoes++;
        if(idBuscado < aux->id){
            atualizarMetricas(comparacoes);
            aux = aux->esq;
        }
        else if(idBuscado > aux->id){
            atualizarMetricas(comparacoes);
            aux = aux->dir;

        }else{
            atualizarMetricas(comparacoes);
            return aux->review;
        }
    }
    high_resolution_clock::time_point end = high_resolution_clock::now();
    double time = duration_cast<duration<double>>(end - start).count();
    atualizarMetricas(comparacoes);

    return NULL;
}

void ArvoreVP::atualizarMetricas(double comparacoes) {
    metricas.comparacoes += comparacoes;
}
int ArvoreVP::getComparacoes() {
    return metricas.comparacoes;
}
