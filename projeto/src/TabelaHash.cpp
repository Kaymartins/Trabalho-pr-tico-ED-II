//
// Created by Kayan on 09/11/2022.
//

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
{}

void TabelaHash::inserirItem(int key, string value)
{}

void TabelaHash::removerItem(int key)
{}

string TabelaHash::pesquisarItem(int key)
{}

void TabelaHash::printTable()
{}