
//
// Created by Kayan on 23/10/2022.
//

#include <iostream>

using namespace std;
void Merge(int *a, int low, int high, int mid)
{

	int i, j, k, temp[high-low+1]; // temp = vetor temporario. low = inicio do vetor, high final do vetor. mid = meio do vetor. a array a ser ordenada
	i = low;
	k = 0;
	j = mid + 1;

	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
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


	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}


	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}



	for (i = low; i <= high; i++)
	{
		a[i] = temp[i-low];
	}
}

void MergeSort(int *a, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		MergeSort(a, low, mid);
		MergeSort(a, mid+1, high);

		Merge(a, low, high, mid);
	}

}


void swap(int *a, int *b) {
  int aux = *a;
  *a = *b;
  *b = aux;
}


void printArray(int array[], int size) {
  int i;
  for (i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}


int partition(int array[], int low, int high) {


  int pivot = array[high];


  int i = (low - 1);


  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {


      i++;


      swap(&array[i], &array[j]);
    }
  }


  swap(&array[i + 1], &array[high]);

  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {


    int pi = partition(array, low, high);


    quickSort(array, low, pi - 1);

    quickSort(array, pi + 1, high);
  }
}




void countSort(int array[], int size)
{
  int output[100];// nesses vetores temos que alocar o tamanho dele pro max de registros possiveis + 1
  int count[100];
  int max = array[0];

  for (int i = 1; i < size; i++) {
    if (array[i] > max)
      max = array[i];
  }


  for (int i = 0; i <= max; ++i) {
    count[i] = 0;
  }

  for (int i = 0; i < size; i++) {
    count[array[i]]++;
  }

  for (int i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }
  for (int i = size - 1; i >= 0; i--) {
    output[count[array[i]] - 1] = array[i];
    count[array[i]]--;
  }


  for (int i = 0; i < size; i++) {
    array[i] = output[i];
  }
}

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
    printArray(vet, n);
    cout << "Vetor ordenado com mergeSort: \n";
    printArray(vet2, n2);
     cout << "Vetor ordenado com countSort: \n";
    printArray(vet3, n3);
    return 0;
}


