#include "../headers/RegistroHash.h"
#include "../headers/ArvoreB.h"

NoBtree* ArvoreB::criaNo(ProductReview* chave, NoBtree* filho)
{
    NoBtree* no = new NoBtree;
    no->chave[1] = chave;
    no->n = 1;
    no->filho[0] = raiz;
    no->filho[1] = filho;
    no->folha = true;

    if(chave != 0)
        no->id[1] = chave->getUserId() + chave->getProductId();

    return no;
}

void ArvoreB::dividirFilho(NoBtree* x, int i)
{
    cout << "entrou no split ent ? "<< endl;
    NoBtree* z = criaNo(0, nullptr);
    
    NoBtree* y = x->filho[i];
    cout<< y->folha <<endl;
    z->folha = y->folha;
    
    z->n = NO_MAX / 2;
    

    for (int j = 1; j <= NO_MAX / 2; j++)
        z->chave[j] = y->chave[j + NO_MAX / 2];

    if (y->folha == false) {
        for (int j = 1; j <= NO_MAX / 2; j++)
            z->filho[j] = y->filho[j + NO_MAX / 2];
    }

    y->n = NO_MAX / 2;

    for (int j = x->n + 1; j > i + 1; j--)
        x->filho[j + 1] = x->filho[j];

    x->filho[i + 1] = z;

    for (int j = x->n; j >= i; j--)
        x->chave[j + 1] = x->chave[j];

    x->chave[i] = y->chave[NO_MAX / 2];
    x->n = x->n + 1;
    cout << "saiu do split ent ?" <<endl; 
}

void ArvoreB::insertNonFull(NoBtree* x, ProductReview* chave)
{
    int i = x->n;
    cout << "entrou no insere" << endl;

    if (x->folha) {
        while (i >= 1 && chave->getUserId() + chave->getProductId() < x->chave[i]->getUserId() + x->chave[i]->getProductId()) {
            x->chave[i + 1] = x->chave[i];
            x->id[i + 1] = x->id[i];
            i--;
        }

        x->chave[i+1] = chave;
        x->id[i+1] = chave->getUserId() + chave->getProductId();
        x->n++;
    } else {
        cout << x->id[1] << endl;
        while (i >= 1 && chave->getUserId() + chave->getProductId() < x->chave[i]->getUserId() + x->chave[i]->getProductId()) {
            i--;
        }
        cout << "saiu do while" << endl;
        i++;

        if (x->filho[i]->n == NO_MAX) {
            dividirFilho(x, i);

            if (chave->getUserId() + chave->getProductId() > x->chave[i]->getUserId() + x->chave[i]->getProductId()) {
                i++;
            }
        }

        insertNonFull(x->filho[i], chave);
    }
}

void ArvoreB::insere(ProductReview* chave)
{
    if (raiz == nullptr) {
        raiz = criaNo(chave, nullptr);
    }
    else {
        if (raiz->n == NO_MAX) {   
            NoBtree* s = criaNo(0, nullptr);
            raiz = s;
            s->folha = false;
            s->filho[0] = raiz;
            dividirFilho(s, 0);
            insertNonFull(s, chave);
        }
        else
            cout << "aaaa" << endl;
            insertNonFull(raiz, chave);
    }
}

ProductReview* ArvoreB::busca(ProductReview* chave)
{
    NoBtree* x = raiz;
    while (x != nullptr) {
        int i = 0;
        while (i < x->n && chave->getUserId() + chave->getProductId() > x->chave[i]->getUserId() + x->chave[i]->getProductId())
            i++;
        if (i < x->n && chave->getUserId() + chave->getProductId() == x->chave[i]->getUserId() + x->chave[i]->getProductId())
            return x->chave[i];
        x = x->filho[i];
    }
    return nullptr;
}

void ArvoreB::print()
{
    imprimirAux(raiz);
}

void ArvoreB::imprimirAux(NoBtree* raiz)
{
    int i;
    for(i = 0; i < raiz->n; i++) {
        if(raiz->folha == false){
            imprimirAux(raiz->filho[i]);
        }
        cout << raiz->chave[i+1]->getUserId() + raiz->chave[i+1]->getProductId() << endl;
    }
    if(raiz->folha == false){
        imprimirAux(raiz->filho[i]);
    }
}