//
// Created by Kayan on 23/10/2022.
//

#include <iostream>

using namespace std;

int main()
{
    int sortOrHash;

    //chama a função createBinary para criar o arquivo binário
    
    cout << "Digite 1 para analise de algoritmos de ordenacao ou 2 para etapa de tabelaHash de Produtos mais avaliados: ";
    cin >> sortOrHash;

    if(sortOrHash == 1){
        int M = 3; //quantidade de cojutos de dados para analise
        int N[5] = {10000, 50000, 100000, 500000, 1000000}; //quantidade de dados para analise
        float tempo[3]; //vetor para armazenar o tempo de execução de cada algoritmo


        for(int i = 0; i < M; i++){ //executa o algoritmo de mergeSort para cada conjunto de dados
            tempo[0] += mergeSort(vet[i]);            
        }
        tempo[0] /= M; //calcula a média do tempo de execução do algoritmo de mergeSort

        for(int i = 0; i < M; i++){ //executa o algoritmo de quickSort para cada conjunto de dados
            tempo[1] += quickSort(vet[i]);            
        }
        tempo[1] /= M; //calcula a média do tempo de execução do algoritmo de quickSort

        for(int i = 0; i < M; i++){ //executa o algoritmo de countSort para cada conjunto de dados
            tempo[2] += countSort(vet[i]);            
        }
        tempo[2] /= M; //calcula a média do tempo de execução do algoritmo de countSort

        //imprime os resultados
        cout << "Tempo medio de execucao do algoritmo de mergeSort: " << tempo[0] << endl;
        cout << "Tempo medio de execucao do algoritmo de quickSort: " << tempo[1] << endl;
        cout << "Tempo medio de execucao do algoritmo de countSort: " << tempo[2] << endl;
    }
    else if(sortOrHash == 2){
        //Eecuta a etapa de tabelaHash de Produtos mais avaliados
    }
    else{
        cout << "Opcao invalida!" << endl;
        cout << "Saindo do Programa" << endl;
    }    
}


