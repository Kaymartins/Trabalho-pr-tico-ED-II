#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>


using namespace std;

struct HuffmanNo
{
    char c; //caractere
    int freq; //frequencia do nó
    HuffmanNo *esq, *dir; //ponteiros para os filhos

    HuffmanNo(char c, int freq)
    {
        esq = dir = NULL;
        this->c = c;
        this->freq = freq;
    }

    HuffmanNo()
    {
        esq = dir = NULL;
    }

};

struct comparaNos
{
    bool operator()(HuffmanNo* esq, HuffmanNo* dir)
    {
        return (esq->freq > dir->freq);
    }
};

class Huffman{
    private:
        HuffmanNo* raiz;
        int nComparacoes;
        unordered_map<char, string> codigo;
        void codigoHuffman(HuffmanNo* raiz, string str);
    public:
    void huffman(string str);
    void print(HuffmanNo* raiz, string str);
    string comprime(string str);
    string descomprime(string str, unordered_map<char, string> cod);
    unordered_map<char, string> getCodigo();
    int getComparacoes(){return nComparacoes;};
    int aumentaComparacoes(int n){return nComparacoes += n;};
    int taxaCompressao(string stringOriginal, string stringComprimido);
    
};


#endif