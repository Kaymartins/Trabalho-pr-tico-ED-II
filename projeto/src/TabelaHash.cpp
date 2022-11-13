#include "../headers/TabelaHash.h"
#include <iostream>
#include <fstream>

#include <list>

using namespace std;

TabelaHash::TabelaHash(int n)
{
    cont = n;
    table = new list<int>[cont];

}

TabelaHash::~TabelaHash()
{}

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

int TabelaHash::funcaoHash(int key)
{
    //Método da divisão:
    return key % cont;
}

void TabelaHash::inserirItem(int key)
{
    //calcula índice da chave na tabela:
     table[funcaoHash(key)].push_back(key);
}

// void TabelaHash::removerItem(int key)
// {}

 void TabelaHash::pesquisarItem(int val)
 {
      int key = funcaoHash(val);
        
        for (int j:table[key]){
            if(j == val)
                cout << "valor encontrado";
            else
                cout << "valor não encontrado";
        }
 }

void TabelaHash::printTable(){
    for(int i = 0; i < cont; i++){
      cout << "Index " << i << ": ";
      for(int j : table[i])
        cout << j << " => ";
      cout << endl;
    }
  }
