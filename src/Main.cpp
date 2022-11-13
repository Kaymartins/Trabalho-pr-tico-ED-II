
//
// Created by Kayan on 23/10/2022.
//

#include <iostream>
#include "../headers/sorts.h"

using namespace std;

// void Merge(int *a, int inicio, int final, int meio)
// {

// 	int i, j, k, *temp;
//   temp = new int[final - inicio + 1]; // temp = vetor temporario. inicio = inicio do vetor, final = final do vetor. meio = meio do vetor. a vet a ser ordenada
// 	i = inicio;
// 	k = 0;
// 	j = meio + 1;

// 	while (i <= meio && j <= final)
// 	{
// 		if (a[i] < a[j])
// 		{
// 			temp[k] = a[i];
// 			k++;
// 			i++;
// 		}
// 		else
// 		{
// 			temp[k] = a[j];
// 			k++;
// 			j++;
// 		}
// 	}


// 	while (i <= meio)
// 	{
// 		temp[k] = a[i];
// 		k++;
// 		i++;
// 	}


// 	while (j <= final)
// 	{
// 		temp[k] = a[j];
// 		k++;
// 		j++;
// 	}



// 	for (i = inicio; i <= final; i++)
// 	{
// 		a[i] = temp[i-inicio];
// 	}

//   delete [] temp;
// }

// void MergeSort(int *a, int inicio, int final)
// {
// 	int meio;
// 	if (inicio < final)
// 	{
// 		meio=(inicio+final)/2;
// 		MergeSort(a, inicio, meio);
// 		MergeSort(a, meio+1, final);

// 		Merge(a, inicio, final, meio);
// 	}

// }

// void swap(int *a, int *b) {
//   int aux = *a;
//   *a = *b;
//   *b = aux;
// }

// void printVetor(int vet[], int size) {
//   int i;
//   for (i = 0; i < size; i++)
//     cout << vet[i] << " ";
//   cout << endl;
// }

// int particao(int vet[], int inicio, int final) {


//   int pivot = vet[final];


//   int i = (inicio - 1);


//   for (int j = inicio; j < final; j++) {
//     if (vet[j] <= pivot) {


//       i++;


//       swap(&vet[i], &vet[j]);
//     }
//   }


//   swap(&vet[i + 1], &vet[final]);


//   return (i + 1);
// }

// void quickSort(int vet[], int inicio, int final) {
//   if (inicio < final) {


//     int pi = particao(vet, inicio, final);


//     quickSort(vet, inicio, pi - 1);

//     quickSort(vet, pi + 1, final);
//   }
// }

// void countSort(int vet[], int size)
// {
//   int output[100];// nesses vetores temos que alocar o tamanho dele pro max de registros possiveis + 1
//   int count[100];
//   int max = vet[0];

//   for (int i = 1; i < size; i++) {
//     if (vet[i] > max)
//       max = vet[i];
//   }


//   for (int i = 0; i <= max; ++i) {
//     count[i] = 0;
//   }

//   for (int i = 0; i < size; i++) {
//     count[vet[i]]++;
//   }

//   for (int i = 1; i <= max; i++) {
//     count[i] += count[i - 1];
//   }
//   for (int i = size - 1; i >= 0; i--) {
//     output[count[vet[i]] - 1] = vet[i];
//     count[vet[i]]--;
//   }


//   for (int i = 0; i < size; i++) {
//     vet[i] = output[i];
//   }
// }

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


