#include "../headers/TabelaHash.h"


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
    return key % hashGroups;
}

void TabelaHash::inserirItem(int key, string value)
{}

void TabelaHash::removerItem(int key)
{}

string TabelaHash::pesquisarItem(int key)
{}

void TabelaHash::printTable()
{}