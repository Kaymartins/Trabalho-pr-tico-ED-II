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

    this->table = createTable(n);

}

TabelaHash::~TabelaHash()
{
    delete[] this->table;
}

TabelaHash::RegistroHash* TabelaHash::createTable(int n)
{
    RegistroHash *table = new RegistroHash[n];
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
    const int p = 31, m = 1e9 + 9;
    int hash = 0;
    long long p_pow = 1;

    for (int i = 0; i < s.length(); i++){
        hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
        cout << "hash: " << hash << endl;
        p_pow = (p_pow * p) % m;
    }
    cout << "hash: " << abs(hash % n)  << endl;
    return abs(hash) % n;
}

/*
int TabelaHash::funcaoHash(int key)
{
    //Método da divisão:
    return key % cont;
}
*/

void TabelaHash::inserirItem(string value)
{
    int index = hashPolinomial(value,total);
    cout << "index: " << index << endl;
    //calcula índice da chave na tabela:
    if(this->table[index].size() > 0){
        colisoes++;
    }
     this->table[index].push_back(value);
     this->cont++;
}


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


 void TabelaHash::pesquisarItem(string val)
 {
      int key = hashPolinomial(val,total);
        
        for (string j:table[key])
        {
            if(j == val)

                cout << "valor " << val << "encontrado" << endl;
        }
 }


void TabelaHash::printTable(){
    for(int i = 0; i < cont; i++){
      cout << "Index " << i << ": ";
      for(string j : table[i])
        cout << j << " => ";
      cout << endl;
    }
  }
