#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <iostream>
#include <string>
#include "Huffman.h"

using namespace std;

class Queue {
  private:
    int front, size;
    int capacity = 96;
    HuffmanNo* queue;
    void minHeapify(int i);

  public:
    Queue();
    ~Queue();
    bool isFull();
    bool isEmpty();
    void enqueue(HuffmanNo item);
    void dequeue();
    int getSize();
    HuffmanNo getFront();
};

Queue::Queue() {
  front = this->size = 0;
  queue = new HuffmanNo[capacity];
}

Queue::~Queue() {
  delete[] queue;
}

bool Queue::isFull() {
  return (this->size == this->capacity);
}

bool Queue::isEmpty() {
  return (this->size == 0);
}

void Queue::enqueue(HuffmanNo item) {
  if (isFull()) {
    return;
  }
    this->queue[this->size] = item;
    this->size++;
    this->minHeapify(this->size - 1);
}

void Queue::dequeue() {
  if (isEmpty()) {
    throw "empty queue";
  }
        this->queue[0] = this->queue[this->size - 1];
        this->size--;
        this->minHeapify(0);

}

void Queue::minHeapify(int index){
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


HuffmanNo Queue::getFront() {
  if (isEmpty()) {
    cout << "empty queue" << endl;
    exit(0);
  }
  return this->queue[this->front];
}

int Queue::getSize(){
    return this->size;
}


#endif