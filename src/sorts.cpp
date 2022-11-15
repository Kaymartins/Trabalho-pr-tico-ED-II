#include "../headers/sorts.h"
#include "../headers/ProductReview.h"
#include <iostream>
#include <math.h>
const int RUN = 32;

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
  
  //realiza a ordenação do vetor original recebido como parâmetro no vetor temporário:
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
void trocar(T *a, T *b) {
  //Realiza a troca de valores entre A e B:
  T aux = *a;
  *a = *b;
  *b = aux;
}

void printVetor(ProductReview vet[], int size) {
  //Imprime o vetor:
  for (int i = 0; i < size; i++)
    cout << vet[i].getUserId() << " ";
  cout << endl;
}

int particao(ProductReview vet[], int inicio, int final) 
{
  //define o pivô como o último elemento do vetor:
  int pivo = stoi(vet[final].getUserId());

  //inicializa variável auxiliar com "-1":
  int i = (inicio - 1);
  
  //percorre o vetor:
  for (int j = inicio; j < final; j++) 
  {
    //se o valor do elemento do vetor for menor que o pivô, posiciona o elemento no começo do vetor:
    if (stoi(vet[j].getUserId()) <= pivo) {
      i++;
      trocar(&vet[i], &vet[j]);
    }
  }

  //troca os elementos do pivô com o elemento do índice "i+1":
  trocar(&vet[i + 1], &vet[final]);

  //retorna o índice inicial dessa partição do vetor:
  return (i + 1);
}

void quickSort(ProductReview vet[], int inicio, int final) {

  if (inicio < final) {

    //calcula o índice do pivô:
    int indicePart = particao(vet, inicio, final);

    //realiza a ordenação do vetor em duas partes:
    quickSort(vet, inicio, indicePart - 1);
    quickSort(vet, indicePart + 1, final);
  }
}

// void countSort(int vet[], int size)
// {
//   int *output = new int[size + 1];
//   int *count = new int[size + 1];
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

void insertionSort(ProductReview *vet, int esq, int dir)
{
	for (int i = esq + 1; i <= dir; i++)
	{
		ProductReview temp = vet[i];
		int j = i - 1;
		while (j >= esq && stoi(vet[j].getUserId()) > stoi(temp.getUserId()))
		{
			vet[j+1] = vet[j];
			j--;
		}
	  vet[j+1] = temp;
	}
}

void timSort(ProductReview *vet, int n)
{
	// divide o vetor em varios subvetores(nesse caso de 32 posições(o valorde RUN))
  // e ordena cada uma dessas posicoes individualmente
	for (int i = 0; i < n; i+=RUN)
		insertionSort(vet, i, min((i+RUN-1),(n-1)));

	for (int size = RUN; size < n; size = 2*size)
	{
		
		// pick starting point of
		// esq sub array. We
		// are going to merge
		// vet[esq..esq+size-1]
		// and vet[esq+size, esq+2*size-1]
		// After every merge, we
		// increase esq by 2*size
		for (int esq = 0; esq < n;	esq += 2*size)
		{
			
			// find ending point of
			// esq sub array
			// mid+1 is starting point
			// of dir sub array
			int mid = esq + size - 1;
			int dir = min((esq + 2*size - 1),(n-1));

			// merge sub array vet[esq.....mid] &
			// vet[mid+1....dir]
			if(mid < dir) 
        Merge(vet, esq, dir, mid);
		}
	}
}


