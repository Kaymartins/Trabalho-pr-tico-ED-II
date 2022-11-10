//
// Created by Kayan on 09/11/2022.
//
#include<iostream>
#include<list>
#include<cstring>
#include<string>

#ifndef ED_II_TABELAHASH_H
#define ED_II_TABELAHASH_H


class TabelaHash {
private:
    int cont;
    int chave;
    string chave;
    int hasGroups = 10;
    list<pair<int, string>> table[hasGroups]; //balde;

public:
    bool tabelaVazia();
    int funcaoHash(int key);
    void inserirItem(int key, string value);
    void removerItem(int key);
    string pesquisarItem(int key);
    void printTable();
};

bool HashTable::tabelaVazia(){
    int sum = 0;
    for(int i = 0; i < hashGroups; i++){
        sum += table[i].size();
    }

    if(!sum){
        return true;
    }

    return false;
}


#endif //ED_II_TABELAHASH_H
