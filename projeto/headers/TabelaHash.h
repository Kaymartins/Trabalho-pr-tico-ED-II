#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED

#include <string>
#include <list>

using namespace std;

class TabelaHash{
private:
    //total linhas
    int cont;
    int total;
    //    int chave;
    //    string chave;
    list<string> *table;

    int colisoes;

public:
    TabelaHash(int n);
    ~TabelaHash();
    bool tabelaVazia();
    int funcaoHash(int key);
    int hashPolinomial(string &s, int &n);
    void inserirItem(string value);
    void removerItem(string value);
    void pesquisarItem(string val);
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