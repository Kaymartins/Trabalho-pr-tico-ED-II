#include "ProductReview.h"
#include "RegistroHash.h"

//<<----------------- MÉTODOS GERAIS ----------------->>

template <typename T>
void trocar(T *a, T *b);

void printVetor(ProductReview vet[], int size);

//<<----------------- MERGE SORT ----------------->>

void merge(ProductReview *a, int inicio, int final, int meio, int *metricasOrdenacao);

void mergeSort(ProductReview *a, int inicio, int final, int *metricasOrdenacao);

//<<----------------- QUICK PRODUCTREVIEW SORT ----------------->>

int particao(ProductReview vet[], int inicio, int final, int *metricasOrdenacao);

void quickSort(ProductReview vet[], int inicio, int final, int *metricasOrdenacao);

//<<----------------- QUICK REGISTROHASH SORT ----------------->>

int particaoDecrescente(RegistroHash vet[], int inicio, int final);

void quickSortDecrescente(RegistroHash vet[], int inicio, int final);

//<<----------------- TIM SORT ----------------->>

void insertionSort(ProductReview *vet, int esq, int dir, int *metricasOrdenacao);

void timSort(ProductReview *vet, int n, int *metricasOrdenacao);

