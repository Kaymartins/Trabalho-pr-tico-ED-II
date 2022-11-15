#include "../headers/RegistroHash.h"
#include "../headers/TabelaHash.h"

#include <iostream>
#include <fstream>

#include <list>

using namespace std;

//cria tabela hash:
TabelaHash::TabelaHash(int n)
{
    this->total = n;
    this->cont = 0;
    this->colisoes = 0;

    //define o tamanho da tabela:
    this->primo = criaPrimo(n);
    cout << "Primo: " << primo << endl;

    //cria a tabela com tamanho primo:
    this->table = createTable(primo);
}

//desaloca a memória da tabela:
TabelaHash::~TabelaHash()
{
    //desaloca a memória da tabela:
    delete[] this->table;
}


//cria a tabela com tamanho primo:
list<RegistroHash> *TabelaHash::createTable(int n)
{
    //declara lista de registros hash para a tabela:
    list<RegistroHash> *table = new list<RegistroHash>[n];

    //retorna a tabela criada:
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


//define o tamanho da tabela hash como o número primo mais próximo:
int TabelaHash::criaPrimo(int n){

    //define variáveis auxiliares:
    int i, j;
    bool flag = false;
    
    //atualiza n para o próximo número primo:
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

    //retorna o número primo:
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




