#include "../headers/sorts.h"
#include <../headers/ProductReview.h>
#include <iostream>

using namespace std;

void Merge(ProductReview *a, int inicio, int final, int meio)
{

	int i, j, k;
  ProductReview *temp;
  temp = new ProductReview[final - inicio + 1]; // temp = vetor temporario. inicio = inicio do vetor, final = final do vetor. meio = meio do vetor. a vet a ser ordenada
	i = inicio;
	k = 0;
	j = meio + 1;

	while (i <= meio && j <= final)
	{
		if (stoi(a[i].getUserId()) < stoi(a[j].getUserId()))
		{
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}


	while (i <= meio)
	{
		temp[k] = a[i];
		k++;
		i++;
	}


	while (j <= final)
	{
		temp[k] = a[j];
		k++;
		j++;
	}



	for (i = inicio; i <= final; i++)
	{
		a[i] = temp[i-inicio];
	}

  delete [] temp;
}

void MergeSort(ProductReview *a, int inicio, int final)
{
	int meio;
	if (inicio < final)
	{
		meio=(inicio+final)/2;
		MergeSort(a, inicio, meio);
		MergeSort(a, meio+1, final);

		Merge(a, inicio, final, meio);
	}

}

template <typename T>

void swap(T *a, T *b) {
  T aux = *a;
  *a = *b;
  *b = aux;
}

void printVetor(ProductReview vet[], int size) {
  int i;
  for (i = 0; i < size; i++)
    cout << vet[i].getUserId() << " ";
  cout << endl;
}

int particao(ProductReview vet[], int inicio, int final) {


  int pivot = stoi(vet[final].getUserId());

  int i = (inicio - 1);
  

  for (int j = inicio; j < final; j++) {
    if (stoi(vet[j].getUserId()) <= pivot) {

      i++;

      swap(&vet[i], &vet[j]);
    }
  }

  swap(&vet[i + 1], &vet[final]);

  return (i + 1);
}

void quickSort(ProductReview vet[], int inicio, int final) {

  if (inicio < final) {

    int pi = particao(vet, inicio, final);

    quickSort(vet, inicio, pi - 1);

    quickSort(vet, pi + 1, final);
  }
}

void countSort(int vet[], int size)
{
  int output[100];// nesses vetores temos que alocar o tamanho dele pro max de registros possiveis + 1
  int count[100];
  int max = vet[0];

  for (int i = 1; i < size; i++) {
    if (vet[i] > max)
      max = vet[i];
  }


  for (int i = 0; i <= max; ++i) {
    count[i] = 0;
  }

  for (int i = 0; i < size; i++) {
    count[vet[i]]++;
  }

  for (int i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }
  for (int i = size - 1; i >= 0; i--) {
    output[count[vet[i]] - 1] = vet[i];
    count[vet[i]]--;
  }


  for (int i = 0; i < size; i++) {
    vet[i] = output[i];
  }
}

