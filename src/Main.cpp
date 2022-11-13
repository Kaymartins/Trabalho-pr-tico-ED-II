
//
// Created by Kayan on 23/10/2022.
//

#include <iostream>
#include "../headers/sorts.h"

using namespace std;

int main()
{
    int vet[] = {8, 7, 6, 1, 0, 9, 2};
    int vet2[] = {1, 15, 99, 56, 12, 5, 8};
    int vet3[] = {1, 15, 99, 56, 12, 5, 8};
    int n = sizeof(vet) / sizeof(vet[0]);
    int n2 = sizeof(vet2) / sizeof(vet2[0]);
    int n3 = sizeof(vet3) / sizeof(vet3[0]);

    quickSort(vet, 0, n - 1);
    MergeSort(vet2, 0, n2 - 1);
    countSort(vet3,n3);

    cout << "Vetor ordenado com quickSort: \n";
    printVetor(vet, n);
    cout << "Vetor ordenado com mergeSort: \n";
    printVetor(vet2, n2);
    cout << "Vetor ordenado com countSort: \n";
    printVetor(vet3, n3);
    return 0;
}


