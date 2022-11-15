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

int TabelaHash::hashPolinomial(string &s, int& n){
    const int p = 53, m = 1e9 + 9;
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




