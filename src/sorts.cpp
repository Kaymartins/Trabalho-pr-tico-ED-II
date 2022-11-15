#include "../headers/sorts.h"
#include "../headers/ProductReview.h"
#include <iostream>
#include <math.h>

// Constante usada no timSort
const int RUN = 32;

using namespace std;

//<<----------------- MÉTODOS GERAIS ----------------->>

template <typename T>
void trocar(T *a, T *b)
{
	// Realiza a troca de valores entre A e B:
	T aux = *a;
	*a = *b;
	*b = aux;
}

void printVetor(ProductReview vet[], int size)
{
	// Imprime o vetor:
	for (int i = 0; i < size; i++)
		cout << vet[i].getUserId() << endl;
	cout << endl;
}

//<<----------------- MERGE SORT ----------------->>

void merge(ProductReview *a, int inicio, int final, int meio, int *metricasOrdenacao)
{
	// declara variaveis auxiliares:
	int i, j, k;
	// declara um vetor temporário:
	ProductReview *temp;

	// inicializa o vetor temporário levando em consideração o tamanho do vetor original:
	temp = new ProductReview[final - inicio + 1];

	// inicializa as variáveis auxiliares com os índices de inicio e meio do vetor:
	i = inicio;
	k = 0;
	j = meio + 1;

	// realiza a ordenação do vetor original recebido como parâmetro no vetor temporário:
	while (i <= meio && j <= final)
	{
		if (a[i].getUserId() < a[j].getUserId())
		{
			metricasOrdenacao[0]++;
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			metricasOrdenacao[0]++;
			temp[k] = a[j];
			k++;
			j++;
		}
	}

	// aloca os elementos restantes da primeira parte do vetor original no vetor temporário:
	while (i <= meio)
	{
		temp[k] = a[i];
		k++;
		i++;
	}

	// aloca os elementos restantes da segunda parte do vetor original no vetor temporário:
	while (j <= final)
	{
		temp[k] = a[j];
		k++;
		j++;
	}

	// aloca os elementos do vetor temporário no vetor original:
	for (i = inicio; i <= final; i++)
	{
		metricasOrdenacao[1]++;
		a[i] = temp[i - inicio];
	}

	// libera a memória alocada para o vetor temporário:
	delete[] temp;
}

void mergeSort(ProductReview *a, int inicio, int final, int *metricasOrdenacao)
{
	int meio;
	if (inicio < final)
	{
		// calcula o meio do vetor:
		meio = (inicio + final) / 2;
		// divide o vetor em duas partes:
		mergeSort(a, inicio, meio, metricasOrdenacao);
		mergeSort(a, meio + 1, final, metricasOrdenacao);

		// realiza a ordenação do vetor:
		merge(a, inicio, final, meio, metricasOrdenacao);
	}
}

//<<----------------- QUICK PRODUCTREVIEW SORT ----------------->>

int particao(ProductReview vet[], int inicio, int final, int *metricasOrdenacao)
{
	// define o pivô como o último elemento do vetor:
	string pivo = vet[final].getUserId();

	// inicializa variável auxiliar com "-1":
	int i = (inicio - 1);

	// percorre o vetor:
	for (int j = inicio; j < final; j++)
	{
		// se o valor do elemento do vetor for menor que o pivô, posiciona o elemento no começo do vetor:
		if (vet[j].getUserId() <= pivo)
		{
			metricasOrdenacao[0]++;
			i++;
			trocar(&vet[i], &vet[j]);
			metricasOrdenacao[1]++;
		}
	}

	// troca os elementos do pivô com o elemento do índice "i+1":
	trocar(&vet[i + 1], &vet[final]);
	metricasOrdenacao[1]++;

	// retorna o índice inicial dessa partição do vetor:
	return (i + 1);
}

void quickSort(ProductReview vet[], int inicio, int final, int *metricasOrdenacao)
{
	if (inicio < final)
	{
		// calcula o índice do pivô:
		int indicePart = particao(vet, inicio, final, metricasOrdenacao);

		// realiza a ordenação do vetor em duas partes:
		quickSort(vet, inicio, indicePart - 1, metricasOrdenacao);
		quickSort(vet, indicePart + 1, final, metricasOrdenacao);
	}
}

//<<----------------- QUICK REGISTROHASH SORT ----------------->>

int particaoDecrescente(RegistroHash vet[], int inicio, int final)
{
	// define o pivô como o último elemento do vetor:
	int pivo = vet[final].qtdReviews;

	// inicializa variável auxiliar com "-1":
	int i = (inicio - 1);

	// percorre o vetor:
	for (int j = inicio; j < final; j++)
	{
		// se o valor do elemento do vetor for menor que o pivô, posiciona o elemento no começo do vetor:
		if (vet[j].qtdReviews >= pivo)
		{
			i++;
			trocar(&vet[i], &vet[j]);
		}
	}

	// troca os elementos do pivô com o elemento do índice "i+1":
	trocar(&vet[i + 1], &vet[final]);

	// retorna o índice inicial dessa partição do vetor:
	return (i + 1);
}

void quickSortDecrescente(RegistroHash vet[], int inicio, int final)
{
	if (inicio < final)
	{
		// calcula o índice do pivô:
		int indicePart = particaoDecrescente(vet, inicio, final);

		// realiza a ordenação do vetor em duas partes:
		quickSortDecrescente(vet, inicio, indicePart - 1);
		quickSortDecrescente(vet, indicePart + 1, final);
	}
}

//<<----------------- TIM SORT ----------------->>

void insertionSort(ProductReview *vet, int esq, int dir, int *metricasOrdenacao)
{
	for (int i = esq + 1; i <= dir; i++)
	{
		ProductReview temp = vet[i];
		int j = i - 1;
		while (j >= esq && vet[j].getUserId() > temp.getUserId())
		{
			vet[j + 1] = vet[j];
			metricasOrdenacao[1]++;
			j--;
		}
		vet[j + 1] = temp;
		metricasOrdenacao[1]++;
	}
}

void timSort(ProductReview *vet, int n, int *metricasOrdenacao)
{
	// divide o vetor em varios subvetores(nesse caso de 32 posições(o valorde RUN))
	// e ordena cada uma dessas posicoes individualmente
	for (int i = 0; i < n; i += RUN)
		insertionSort(vet, i, min((i + RUN - 1), (n - 1)), metricasOrdenacao);

	// percorre o vetor criado no insertionSort e faz a ordenação
	for (int size = RUN; size < n; size = 2 * size)
	{
		// faz a junção dos subvetores ordenados
		for (int esq = 0; esq < n; esq += 2 * size)
		{
			int mid = esq + size - 1;
			int dir = min((esq + 2 * size - 1), (n - 1));

			// faz a junção dos subvetores ordenados utilizando o método merge
			if (mid < dir)
				merge(vet, esq, dir, mid, metricasOrdenacao);
		}
	}
}
