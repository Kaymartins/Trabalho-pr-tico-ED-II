#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED

#include "RegistroHash.h"
#include <string>
#include <list>

using namespace std;

class TabelaHash{
private:
    //total linhas
    int cont;
    int primo;
    int total;
    //    int chave;
    //    string chave;
    list<RegistroHash> *table;

    int colisoes;

public:
    TabelaHash(int n);
    ~TabelaHash();
    list<RegistroHash> *createTable(int n);
    RegistroHash *createVetor();
    RegistroHash* ordenaProdutos();
    void imprimirMaisAvaliados(int n);
    int criaPrimo(int n);
    int hashPolinomial(string &s, int &n);
    void inserirItem(string value);
    void printTable();
    void ordenaTabela(int n);
};

#endif // ED_II_TABELAHASH_H