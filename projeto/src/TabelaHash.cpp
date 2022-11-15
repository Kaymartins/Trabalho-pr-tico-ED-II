#include "../headers/RegistroHash.h"
#include "../headers/TabelaHash.h"

#include <iostream>
#include <fstream>

#include <list>

using namespace std;

TabelaHash::TabelaHash(int n)
{
    this->total = n;
    this->cont = 0;
    this->colisoes = 0;

    this->primo = criaPrimo(n);
    cout << "Primo: " << primo << endl;
    this->table = createTable(primo);

}

TabelaHash::~TabelaHash()
{
    delete[] this->table;
}


list<RegistroHash> *TabelaHash::createTable(int n)
{
    list<RegistroHash> *table = new list<RegistroHash>[n];
    return table;
}

// bool TabelaHash::tabelaVazia()
// {
//     //Inicializa variável de soma:
//     int sum = 0;

//     //Soma o tamanho de cada lista:
//     for (int i = 0; i < hashGroups; i++)
//     {
//         sum += table[i].size();
//     }

//     if (!sum)
//     {
//         return true;
//     }

//     return false;
// }

int TabelaHash::hashPolinomial(string &s, int& n){
    const int p = 31, m = 1e9 + 7;
    int hash = 0;
    long long p_pow = 1;

    for (int i = 0; i < s.length(); i++){
        hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return abs(hash) % n;
}

int TabelaHash::criaPrimo(int n){
    int i, j;
    bool flag = false;
    

    while(!flag){
        for(i=2; i<n/2; i++){
            if(n%i == 0){
                flag = false;
                n++;
            }
            else{
                flag = true;
            }
        }
    }
    return n;
}

void TabelaHash::inserirItem(string value)
{
    int index = hashPolinomial(value,total);
    this->cont++;
    //calcula índice da chave na tabela:
    if(this->table[index].size() > 0){
        for(auto it = this->table[index].begin(); it != this->table[index].end(); it++){
            if(it->productId == value){
                it->qtdReviews++;
                return;
            }
        }
        this->colisoes++;
    }
    RegistroHash novoRegistro = {value, 1};
    this->table[index].push_back(novoRegistro);
}

void TabelaHash::printTable(){
    for(int i = 0; i < primo; i++){
      cout << "Index " << i << ": ";
      for(RegistroHash j : table[i])
        cout << "productId: " << j.productId << " qtdReviews: " << j.qtdReviews << " => ";
      cout << endl;
    }

    cout << "Total de colisões: " << this->colisoes << endl;
}

/*
void TabelaHash::removerItem(string value)
{
    int index = hashPolinomial(value,total);
    list<string>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++)
    {
    if (*i == value)
      break;
    }
    if (i != table[index].end())
      table[index].erase(i);
}
*/


/*
 void TabelaHash::pesquisarItem(string val)
 {
      int key = hashPolinomial(val,total);
        
        for (string j:table[key])
        {
            if(j == val)

                cout << "valor " << val << "encontrado" << endl;
        }
 }
 */
 
 RegistroHash* TabelaHash::createVetor()
 {
    RegistroHash* vetor = new RegistroHash[this->cont];
    int j = 0;
    for(int i = 0; i < primo; i++){
        for(RegistroHash k : table[i]){
            vetor[j] = k;
            j++;
        }
    }
    return vetor;
 }

RegistroHash* TabelaHash::ordenaProdutos()
{
    
    RegistroHash* vetor = createVetor();

    quickSort(&vetor,0, cont - 1);

    return vetor;
}

void TabelaHash::imprimirMaisAvaliados(int n)
{
    RegistroHash* vetor = ordenaProdutos();
    
    for (int i = 0; i < n; i++)
    {
        cout << "Produto: " << vetor[i].productId << " - " << vetor[i].qtdReviews << " avaliações" << endl;
    }
    
}

template <typename T>
void trocar(T *a, T *b) {
  //Realiza a troca de valores entre A e B:
  T aux = *a;
  *a = *b;
  *b = aux;
}

int TabelaHash::particao(RegistroHash* vet[],int inicio, int final) 
{
  //define o pivô como o último elemento do vetor:
    
  int pivo = vet[final]->qtdReviews;

  //inicializa variável auxiliar com "-1":
  int i = (inicio - 1);
  
  //percorre o vetor:
  for (int j = inicio; j < final; j++) 
  {
    //se o valor do elemento do vetor for menor que o pivô, posiciona o elemento no começo do vetor:
    if ((vet[j]->qtdReviews) <= pivo) {
      i++;
      trocar(&vet[i], &vet[j]);
    }
  }

  //troca os elementos do pivô com o elemento do índice "i+1":
  trocar(&vet[i + 1], &vet[final]);

  //retorna o índice inicial dessa partição do vetor:
  return (i + 1);
}

void TabelaHash::quickSort(RegistroHash* vet[],int inicio, int final) {

  if (inicio < final) {
    //calcula o índice do pivô:W

    for(int i = 0; i < cont ; i++){
        cout << "Produto: " << vet[i]->productId << " - " << vet[i]->qtdReviews << " avaliações" << endl;
    }
    int indicePart = particao(vet,inicio, final);
    
    //realiza a ordenação do vetor em duas partes:
    quickSort(vet, inicio, indicePart - 1);
    quickSort(vet, indicePart + 1, final);
  }
}


