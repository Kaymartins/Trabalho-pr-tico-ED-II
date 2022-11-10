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
    int estado = -2; // -2 = vazio, -1 = ocupado, x = no índice, 0 = removido;

public:
    bool tabelaVazia();
    int funcaoHash(int key);
    void inserirItem(int key, string value);
    void removerItem(int key);
    string pesquisarItem(int key);
    void printTable();
};

#endif // ED_II_TABELAHASH_H
