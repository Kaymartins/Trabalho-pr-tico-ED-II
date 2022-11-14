#include "../headers/sorts.h"
#include "../headers/ProductReview.h"
#include <iostream>

using namespace std;

void Merge(ProductReview *a, int inicio, int final, int meio)
{
  //declara variaveis auxiliares:
	int i, j, k;
  //declara um vetor temporário:
  ProductReview *temp;

  //inicializa o vetor temporário levando em consideração o tamanho do vetor original:
  temp = new ProductReview[final - inicio + 1];

  //inicializa as variáveis auxiliares com os índices de inicio e meio do vetor:
	i = inicio;
	k = 0;
	j = meio + 1;

  //DEBUG
  cout << "\nNOVO MERGE: " << endl;

  //realiza a ordenação do vetor original recebido como parâmetro no vetor temporário:
	while (i <= meio && j <= final)
	{
    //DEBUG:
    cout << "[DEBUG] i: " << i << " j: " << j << endl;

		if (stoi(a[i].getUserId()) < stoi(a[j].getUserId()))
		{
      //DEBUG:
      cout << "[DEBUG] a[i].getUserId(): " << a[i].getUserId() << " a[j].getUserId(): " << a[j].getUserId() << endl;

			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
      //DEBUG:
      cout << "[DEBUG] a[i].getUserId(): " << a[i].getUserId() << " a[j].getUserId(): " << a[j].getUserId() << endl;

			temp[k] = a[j];
			k++;
			j++;
		}
	}

  //aloca os elementos restantes da primeira parte do vetor original no vetor temporário:
	while (i <= meio)
	{
		temp[k] = a[i];
		k++;
		i++;
	}

  //aloca os elementos restantes da segunda parte do vetor original no vetor temporário:
	while (j <= final)
	{
		temp[k] = a[j];
		k++;
		j++;
	}

  //aloca os elementos do vetor temporário no vetor original:
	for (i = inicio; i <= final; i++)
	{
		a[i] = temp[i-inicio];
	}

  //libera a memória alocada para o vetor temporário:
  delete [] temp;
}

void MergeSort(ProductReview *a, int inicio, int final)
{
	int meio;
	if (inicio < final)
	{
    //calcula o meio do vetor:
		meio=(inicio+final)/2;
    //divide o vetor em duas partes:
		MergeSort(a, inicio, meio);
		MergeSort(a, meio+1, final);

    //realiza a ordenação do vetor:
		Merge(a, inicio, final, meio);
	}
}

template <typename T>
void swap(T *a, T *b) {
  //Realiza a troca de valores entre A e B:
  T aux = *a;
  *a = *b;
  *b = aux;
}

void printVetor(ProductReview vet[], int size) {
  //Imprime o vetor:
  for (int i = 0; i < size; i++)
    cout << vet[i].getUserId() << " \n";
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

