#ifndef ED_II_TABELAHASH_H
#define ED_II_TABELAHASH_H
#include <iostream>
#include <list>
#include <cstring>
#include <string>

using namespace std;

class TabelaHash{
private:
    int cont;
    //    int chave;
    //    string chave;
    static const int hashGroups = 10;
    list<pair<int, string>> table[hashGroups]; // balde;

public:
    TabelaHash();
    ~TabelaHash();
    bool tabelaVazia();
    int funcaoHash(int key);
    void inserirItem(int key, string value);
    void removerItem(int key);
    string pesquisarItem(int key);
    void printTable();
};

#endif // ED_II_TABELAHASH_H

/*
- Vou ler N registros aleatórios e contar quantas vezes 
um mesmo produto se repete;
- Vou criar uma tabela com N registros NÃO repetidos;
- Vou ordenar os registros mais avaliados;
- Vou imprimir os P produtos mais avaliados;
*/