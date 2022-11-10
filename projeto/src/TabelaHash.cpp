#include "../headers/TabelaHash.h"

TabelaHash::TabelaHash()
{}

TabelaHash::~TabelaHash()
{}

bool TabelaHash::tabelaVazia()
{
    //Inicializa variável de soma:
    int sum = 0;

    //Soma o tamanho de cada lista:
    for (int i = 0; i < hashGroups; i++)
    {
        sum += table[i].size();
    }

    if (!sum)
    {
        return true;
    }

    return false;
}

int TabelaHash::funcaoHash(int key)
{
    //Método da divisão:
    return key % hashGroups;
}

void TabelaHash::inserirItem(int key, string value)
{
    //calcula índice da chave na tabela:
    int i = funcaoHash(key);
}

void TabelaHash::removerItem(int key)
{}

string TabelaHash::pesquisarItem(int key)
{}

void TabelaHash::printTable()
{}