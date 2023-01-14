#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include "Huffman.h"
#include <iostream>
using namespace std;

//estrutura de fila adaptada para o Nó do Algoritmo de Huffman
class Fila
{
private:
    HuffmanNo *queue;
    int size;
    HuffmanNo top;
    void minHeapify(int index);

public:
    Fila();
    ~Fila();

    void push(HuffmanNo value);
    void pop();
    int getSize();
    HuffmanNo getTop();

    bool isEmpty();
    void print();
};

Fila::Fila(){
    this->size = 0;
    this->queue = new HuffmanNo[96];
}

Fila::~Fila(){
    delete[] this->queue;
}

bool Fila::isEmpty(){
    return this->size == 0;
}

HuffmanNo Fila::getTop(){
    if (isEmpty())
    {
        cout << "Fila vazia!" << endl;
        exit(1);    
    }

    return this->queue[0];
}

void Fila::push(HuffmanNo element){
    if (this->size == 96)
    {
        cout << "Fila cheia!" << endl;
        exit(1);
    }
    else
    {
        this->queue[this->size] = element;
        this->size++;
        this->minHeapify(this->size - 1);
    }
}

void Fila::pop(){
    if (isEmpty())
        throw "Fila vazia!";
    else
    {
        this->queue[0] = this->queue[this->size - 1];
        this->size--;
        this->minHeapify(0);
    }
}

void Fila::minHeapify(int index){
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < this->size && this->queue[left].freq < this->queue[smallest].freq)
        smallest = left;
    if (right < this->size && this->queue[right].freq < this->queue[smallest].freq)
        smallest = right;
    if (smallest != index)
    {
        HuffmanNo aux = this->queue[index];
        this->queue[index] = this->queue[smallest];
        this->queue[smallest] = aux;
        this->minHeapify(smallest);
    }
}

int Fila::getSize(){
    return this->size;
}

void Fila::print(){
    for (int i = 0; i < this->size; i++)
        cout << this->queue[i].c << " " << this->queue[i].freq << endl;
}


#endif