#include "../headers/RegistroHash.h"
#include "../headers/ArvoreB.h"

NoArvoreB::NoArvoreB(int t, bool folha)
{
    this->t = t;
    this->folha = folha;

    //alocando maximo de numero possivel para as chaves
    keys = new ProductReview[2*t-1];
    filho = new NoArvoreB *[2*t];
    n = 0;
}

NoArvoreB::~NoArvoreB()
{
    delete [] keys;
    for(int i=0; i <= n; i++)
        delete filho[i];
    delete [] filho;
}

void NoArvoreB::imprime()
{
    int i;
    for(i = 0; i < n; i++){
        if(folha == false)
            filho[i]->imprime();
        cout << "userId: " << keys[i].getUserId() << endl; 
        cout << "productId:" <<  keys[i].getProductId() << endl;
        cout << "rating:" <<  keys[i].getRating() << endl;
        cout << "timestamp:" <<  keys[i].getTimestamp() << endl;
    }

    if(folha == false)
        filho[i]->imprime();
}

NoArvoreB* ArvoreB::auxBusca(string userId, string productId)
{
    NoArvoreB* atual = raiz;
    while(atual != nullptr)
    {
        int i = 0;
        this->comp++;
        while(i < atual->n && userId + productId > atual->keys[i].getUserId() + atual->keys[i].getProductId()){
            this->comp++;
            i++;
        }

        this->comp++;
        if(i < atual->n && atual->keys[i].getUserId() + atual->keys[i].getProductId() == userId + productId)
            return atual;

       
        if(atual->folha == true)
            return nullptr;

        atual = atual->filho[i];
    }
    return nullptr;
}

ProductReview* ArvoreB::busca(string userId, string productId)
{

    NoArvoreB* aux = auxBusca(userId, productId);

    if(aux == nullptr)
        return nullptr;
    else
        return aux->keys;

}

void ArvoreB::insere(ProductReview* k)
{   

    int comp = 0;
    if(raiz == nullptr)
    {
        //se a arvore estiver vazia cria novo nó
        raiz = new NoArvoreB(t, true);
        raiz->keys[0] = *k; //insere a chave no primeiro indice do nó
        raiz->n = 1; //aumenta o numero de chaves no nó

    }else{

        //se a raiz estiver cheia aumenta nós da arvore
        if(raiz->n == 2*t-1)
        {
            //cria novo nó e torna ele a nova raiz
            NoArvoreB *s = new NoArvoreB(t, false);
            //faz a antiga raiz ser filho desse nó
            s->filho[0] = raiz;
            //operação de split da arvore
            s->divideFilho(0, raiz);

            this->comp++;
            int i = 0;
            if(s->keys[0].getUserId() + s->keys[0].getProductId() < k->getUserId() + k->getProductId())
                i++;
            s->filho[i]->insereNaoCheio(k, comp);
            aumentaComparacao(comp);

            raiz = s;
        }else{
            raiz->insereNaoCheio(k,comp);
            aumentaComparacao(comp);
        }

    }
}

//insere uma nova chave no nó que nao esta cheio
void NoArvoreB::insereNaoCheio(ProductReview* k, int &comp)
{
    int i = n-1;

    if(folha == true)
    {
        while(i >= 0 && keys[i].getUserId() + keys[i].getProductId() > k->getUserId() + k->getProductId())
        {
            comp++;
            keys[i+1] = keys[i];
            i--;
        }

        keys[i+1] = *k;
        n = n+1;
    }else
    {
        while(i >= 0 && keys[i].getUserId() + keys[i].getProductId() > k->getUserId() + k->getProductId())
        {
            comp++;
            i--;
        }

        if(filho[i+1]->n == 2*t-1)
        {
            divideFilho(i+1, filho[i+1]);
            comp++;
            if(keys[i+1].getUserId() + keys[i+1].getProductId() < k->getUserId() + k->getProductId())
                i++;
        }
        filho[i+1]->insereNaoCheio(k, comp);
    }
    
}

void NoArvoreB::divideFilho(int i, NoArvoreB *y)
{
    NoArvoreB *z = new NoArvoreB(y->t, y->folha);
    z->n = t-1;

    for(int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];


    if( y->folha == false)
    {
        for(int j = 0; j < t; j++)
            z->filho[j] = y->filho[j+t];
    }

    y->n = t-1;
    
    for(int j = n; j >= i+1; j--)
        filho[j+1] = filho[j];

    filho[i+1] = z;

    for(int j= n-1; j >= i; j--)
        keys[j+1] = keys[j];

    keys[i] = y->keys[t-1];

    n = n+1;
}