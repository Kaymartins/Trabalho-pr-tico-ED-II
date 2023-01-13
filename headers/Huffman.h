#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

struct HuffmanNo
{
    char c; //caractere
    int freq; //frequencia do nó
    HuffmanNo *esq, *dir; //ponteiros para os filhos

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
        string codigo[256];
        void codigoHuffman(HuffmanNo* raiz, string str, string codigo[]);
    public:
    HuffmanNo* getNo(char c, int freq, HuffmanNo* esq, HuffmanNo* dir);
    void huffman(string str);
    
    string comprime(string str);
    string descomprime(string str);
    
};


#endif