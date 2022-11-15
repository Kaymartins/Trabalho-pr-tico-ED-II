#include "ProductReview.h"
<<<<<<< HEAD
#include "RegistroHash.h"
=======
>>>>>>> main

//<<----------------- MÉTODOS GERAIS ----------------->>

template <typename T>
void trocar(T *a, T *b);

void printVetor(ProductReview vet[], int size);

//<<----------------- MERGE SORT ----------------->>

void merge(ProductReview *a, int inicio, int final, int meio, int *metricasOrdenacao);

void mergeSort(ProductReview *a, int inicio, int final, int *metricasOrdenacao);

<<<<<<< HEAD
//<<----------------- QUICK PRODUCTREVIEW SORT ----------------->>
=======
//<<----------------- QUICK SORT ----------------->>
>>>>>>> main

int particao(ProductReview vet[], int inicio, int final, int *metricasOrdenacao);

void quickSort(ProductReview vet[], int inicio, int final, int *metricasOrdenacao);

<<<<<<< HEAD
//<<----------------- QUICK REGISTROHASH SORT ----------------->>

int particaoDecrescente(RegistroHash vet[], int inicio, int final);

void quickSortDecrescente(RegistroHash vet[], int inicio, int final);

=======
>>>>>>> main
//<<----------------- TIM SORT ----------------->>

void insertionSort(ProductReview *vet, int esq, int dir, int *metricasOrdenacao);

void timSort(ProductReview *vet, int n, int *metricasOrdenacao);

