#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED

#include <string>
#include <list>

using namespace std;

class TabelaHash{
private:
    int cont;
    //    int chave;
    //    string chave;
    // static const int hashGroups = 10;
    // list<pair<int, string>> table[hashGroups]; // balde;
    list<int> *table;

public:
    TabelaHash(int n);
    ~TabelaHash();
    bool tabelaVazia();
    int funcaoHash(int key);
    void inserirItem(int key);
    void removerItem(int key);
    void pesquisarItem(int val);
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