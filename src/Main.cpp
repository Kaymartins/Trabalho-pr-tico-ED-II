//
// Created by Kayan on 23/10/2022.
//

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    int sortOrHash;

    //chama a função createBinary para criar o arquivo binário
    
    cout << "Digite 1 para analise de algoritmos de ordenacao ou 2 para etapa de tabelaHash de Produtos mais avaliados: ";
    cin >> sortOrHash;

    if(sortOrHash == 1){
        int M = 3; //quantidade de cojutos de dados para analise
        int N[5] = {10000, 50000, 100000, 500000, 1000000}; //quantidade de dados para analise
        double tempo[3]; //vetor para armazenar o tempo de execução de cada algoritmo


        for(int i = 0; i < M; i++){ //executa o algoritmo de mergeSort para cada conjunto de 
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            //mergeSort(/*parametro*/);            
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo[0] += duration_cast<duration<double>>(fim - inicio).count();
        }
        tempo[0] /= M; //calcula a média do tempo de execução do algoritmo de mergeSort

        for(int i = 0; i < M; i++){ //executa o algoritmo de quickSort para cada conjunto de dados
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            //quickSort(vet[i]);
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo[1] += duration_cast<duration<double>>(fim - inicio).count();
        }
        tempo[1] /= M; //calcula a média do tempo de execução do algoritmo de quickSort

        for(int i = 0; i < M; i++){ //executa o algoritmo de countSort para cada conjunto de dados
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            //countSort(vet[i]);            

            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo[2] += duration_cast<duration<double>>(fim - inicio).count();
        }
        tempo[2] /= M; //calcula a média do tempo de execução do algoritmo de countSort

        //imprime os resultados
        cout << "Tempo medio de execucao do algoritmo de mergeSort: " << tempo[0] << " segundos." << endl;
        cout << "Tempo medio de execucao do algoritmo de quickSort: " << tempo[1] << " segundos." << endl;
        cout << "Tempo medio de execucao do algoritmo de countSort: " << tempo[2] << " segundos." << endl;
    }
    else if(sortOrHash == 2){
        //Executa a etapa de tabelaHash de Produtos mais avaliados

        //Cria tabelaHash

        //Insere produtos na tabelaHash

        //Imprime produtos mais avaliados
    }
    else{
        cout << "Opcao invalida!" << endl;
        cout << "Fechando do Programa" << endl;
    }    
}


