#include "ProductReview.h"

void merge(ProductReview *a, int inicio, int final, int meio, int *metricasOrdenacao);

void mergeSort(ProductReview *a, int inicio, int final, int *metricasOrdenacao);

int particao(ProductReview vet[], int inicio, int final, int *metricasOrdenacao);

void printVetor(ProductReview vet[], int size);

void quickSort(ProductReview vet[], int inicio, int final, int *metricasOrdenacao);

// void countSort(int vet[], int size);

void insertionSort(ProductReview *vet, int esq, int dir);

void timSort(ProductReview *vet, int n, int *metricasOrdenacao);

