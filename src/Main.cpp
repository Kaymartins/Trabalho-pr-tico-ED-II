
//
// Created by Kayan on 23/10/2022.
//

#include <iostream>
#include "../headers/sorts.h"
#include "../headers/ProductReview.h"


using namespace std;

int main()
{
    ProductReview *vet = new ProductReview[10];
    
    for(int i = 0; i < 10; i++)
    {
        vet[i].setUserId(to_string(10 - i));
        vet[i].setProductId(to_string(10 - i));
        vet[i].setRating(10 - i);
        vet[i].setTimestamp(to_string(10 - i));
    }

    printVetor(vet, 10);

    quickSort(vet, 0, 9);
    //MergeSort(vet, 0, 9);
    // countSort(vet,10);

    cout << "Vetor ordenado com quickSort: \n";
    // printVetor(vet, 10);
    //cout << "Vetor ordenado com mergeSort: \n";
    printVetor(vet, 10);
    // printVetor(vet2, n2);
    // cout << "Vetor ordenado com countSort: \n";
    // printVetor(vet3, n3);
    return 0;
}


