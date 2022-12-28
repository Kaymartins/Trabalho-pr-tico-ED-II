#include "../headers/RegistroHash.h"
#include "../headers/ArvoreVP.h"

void ArvoreVP::rotacaoEsquerda(No *&raiz, No *&no){
    No *noDir = no->dir;
    no->dir = noDir->esq;

    if(no->dir != NULL)
        no->dir->pai = no;

    noDir->pai = no->pai;

    if(no->pai == NULL)
        raiz = noDir;

    else if(no == no->pai->esq)
        no->pai->esq = noDir;

    else
        no->pai->dir = noDir;

    noDir->esq = no;
    no->pai = noDir;
}

void ArvoreVP::rotacaoDireita(No *&raiz, No *&no){
    No *noEsq = no->esq;
    no->esq = noEsq->dir;

    if(no->esq != NULL)
        no->esq->pai = no;

    noEsq->pai = no->pai;

    if(no->pai == NULL)
        raiz = noEsq;

    else if(no == no->pai->dir)
        no->pai->dir = noEsq;

    else
        no->pai->esq = noEsq;

    noEsq->dir = no;
    no->pai = noEsq;
}

void ArvoreVP::balancearInsercao(No *&raiz, No *&no){
    No *pai = NULL;
    No *avo = NULL;

    while((no != raiz) && (no->cor != PRETO) && (no->pai->cor == VERMELHO)){
        pai = no->pai;
        avo = no->pai->pai;

        if(pai == avo->esq){
            No *tio = avo->dir;

            if(tio != NULL && tio->cor == VERMELHO){
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                no = avo;
            }

            else{
                if(no == pai->dir){
                    rotacaoEsquerda(raiz, pai);
                    no = pai;
                    pai = no->pai;
                }

                rotacaoDireita(raiz, avo);
                swap(pai->cor, avo->cor);
                no = pai;
            }
        }

        else{
            No *tio = avo->esq;

            if((tio != NULL) && (tio->cor == VERMELHO)){
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                no = avo;
            }

            else{
                if(no == pai->esq){
                    rotacaoDireita(raiz, pai);
                    no = pai;
                    pai = no->pai;
                }

                rotacaoEsquerda(raiz, avo);
                swap(pai->cor, avo->cor);
                no = pai;
            }
        }
    }

    raiz->cor = PRETO;
}

No* ABBInsert(No* raiz, No* no){

    /*se a arvore é vazia retorna um novo nó*/
    if(raiz == NULL)
        return no;

    /*senão, percorre a arvore*/
    if(no->id < raiz->id){
        raiz->esq = ABBInsert(raiz->esq, no);
        raiz->esq->pai = raiz;
    }

    else if(no->id > raiz->id){
        raiz->dir = ABBInsert(raiz->dir, no);
        raiz->dir->pai = raiz;
    }

    /*retorna a raiz (sem alterações)*/
    return raiz;
}

void ArvoreVP::insere(ProductReview* pr){
    No *novo = new No(pr);
    
    raiz = ABBInsert(raiz, novo);

    balancearInsercao(raiz, novo);
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

void ArvoreVP::imprimir(){
    imprimirAux(raiz);
}

ProductReview* ArvoreVP::busca(string userId, string productId){
    string idBuscado = userId + productId;
    No *aux = raiz;
    
    while(aux != NULL){
        if(idBuscado < aux->id)
            aux = aux->esq;

        else if(idBuscado > aux->id)
            aux = aux->dir;

        else
            return aux->review;
    }

    return NULL;
}

