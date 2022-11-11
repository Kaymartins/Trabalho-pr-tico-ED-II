#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <random>
#include <sstream>
#include <chrono>


#include "../headers/ProductReview.h"

using namespace std;
using namespace std::chrono;

default_random_engine gen;

const int MAX = 7824483;

void ampliaVetor(ProductReview *vet, int *tam)
{
    // cria um novo vetor auxiliar com o dobro do tamanho original:
    ProductReview *aux = new ProductReview[(*tam) * 2];

    // copia os dados do vetor original para o vetor auxiliar:
    for (int i = 0; i < *tam; i++)
    {
        aux[i] = vet[i];
    }

    // libera o espaço de memória do vetor original:
    delete[] vet;

    // passa o endereço do vetor auxiliar para o vetor original:
    vet = aux;

    // atualiza o tamanho do vetor original:
    *tam = (*tam) * 2;
}


void carregaArquivoPorBlocos(string &path, int tamBloco)
{
    ifstream arq(path);
    ProductReview* reviews = new ProductReview[tamBloco];

    

    if(arq.is_open())
    {
        cout << "Criando arquivo binario ... " << endl;
        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        int i = 0;
        string str;

        while(!arq.eof())
        {   
            /*
            char *auxUserId = new char [21];
            char *auxProductId = new char [10];
            char *auxTimestamp = new char[10];
            auxUserId[21] = '\0';
            auxProductId[10] = '\0';
            auxTimestamp[10] = '\0';
            */
            string userId, productId, timestamp, strRating;

            
            getline(arq,userId,',');
            getline(arq,productId,',');
            getline(arq,strRating,',');
            getline(arq,timestamp,'\n');

            /*
            arq.read(reinterpret_cast<char*>(auxUserId), 21);
            arq.read(reinterpret_cast<char*>(auxProductId), 10);
            arq.read(reinterpret_cast<char*>(&rating), sizeof(float));
            arq.read(reinterpret_cast<char*>(auxTimestamp), 10);
            */
            

            // seta os dados do objeto para ProductReview:
            float rating;
            
            reviews[i].setUserId(userId);
            reviews[i].setProductId(productId);
            rating = stof(strRating);
            reviews[i].setRating(rating);
            reviews[i].setTimestamp(timestamp);
            

            i++;
        }
        
        
        
        ofstream file;
        file.open("../../archive/reviews.bin", ios::binary);
        if(file.is_open())
        {
            for(int i = 0; i < tamBloco; i++)
            {
                file.write(reinterpret_cast<char*>(&reviews[i]), sizeof(ProductReview));
            }
        }
        file.close();
        
        

        cout << "Arquivo binario criado com sucesso!" << endl;
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
    }    

    arq.close();
}

void createBinary(string &path)
{
    // abre o arquivo de texto no diretório path:
    ifstream arq(path);

    // cria vetor de objetos ProductReview:
    int tam = 100;
    ProductReview *reviews = new ProductReview[tam];

    if (!arq.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo!" << endl;
        return;
    }

    // lê o arquivo de texto e armazena no vetor de objetos:
    int i = 0;
    while (!arq.eof())
    {
        if (i == tam)
        {
            ampliaVetor(reviews, &tam);
        }

        string userId, productId, strRating, timestamp;
        float rating;

        // lê cada linha do arquivo de texto e armazena os dados em uma string:
        getline(arq, userId, ',');
        getline(arq, productId, ',');
        getline(arq, strRating, ',');
        getline(arq, timestamp, '\n');

        // seta os dados do objeto para ProductReview:
        reviews[i].setUserId(userId);
        reviews[i].setProductId(productId);
        rating = stof(strRating);
        reviews[i].setRating(rating);
        reviews[i].setTimestamp(timestamp);
        // atualiza o contador:
        i++;
    }



    // fecha o arquivo de texto:
    arq.close();

    // abre o arquivo binário:
    ofstream file;
    file.open("../archive/reviews.bin", ios::binary);

    if (!file.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo!" << endl;
        return;
    }

    // escreve o arquivo binário:
    for (i = 0; i < tam; i++)
    {
        file.write((char *)&reviews[i], sizeof(ProductReview));
    }
}


void getReview(int i)
{
    // abre o arquivo binário para leitura:
    ifstream arqBin("../../archive/reviews.bin", ios::binary);

    if (!arqBin.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo!" << endl;
        return;
    }

    // posiciona o cursor no registro i:
    arqBin.seekg(i * sizeof(ProductReview));

    // // lê o registro i:
    // ProductReview review;
    // arqBin.read((char *)&review, sizeof(ProductReview));

    // inicializa variável do tipo ProductReview:
    ProductReview *review = new ProductReview;

    // lê o registro i:
    arqBin.read((char *)review, sizeof(ProductReview));
    review->print();

    /*
    // inicializa variáveis de dados auxiliares:
    string userId, productId, strRating, timestamp;
    float rating;

    // lê cada linha do arquivo de texto e armazena os dados em uma string:
    getline(arqBin, userId, ',');
    getline(arqBin, productId, ',');
    getline(arqBin, strRating, ',');
    getline(arqBin, timestamp, '\n');

    // seta os dados do objeto para ProductReview:
    review.setUserId(userId);
    review.setProductId(productId);
    rating = stof(strRating);
    review.setRating(rating);
    review.setTimestamp(timestamp);
    */

    // fecha o arquivo binário:
    arqBin.close();

}

bool verificaSorteado(int *vet, int i)
{
    for (int j = 0; j < i; j++)
    {
        if (vet[i] == vet[j]){
            return true;
        }
    }
    return false;

   
}


ProductReview* import(int n)
{
    // abre o arquivo binário para leitura:
    ifstream arqBin("../../archive/reviews.bin", ios::binary);

    if (!arqBin.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo!" << endl;
        return NULL;
    }

    // cria vetor de objetos ProductReview com n posições:
    ProductReview *reviews = new ProductReview[n];

    // cria vetor auxiliar com índices sorteados de 0 a n-1:
    int *vet = new int[n];

    // lê o arquivo binário e armazena no vetor aleatório de objetos:
    for (int i = 0; i < n; i++)
    {
        // sorteia um número aleatório entre 0 e n-1:
        uniform_int_distribution<> dist(0, MAX);

        int aux = dist(gen);

        vet[i] = aux;

        // verifica se o número sorteado já foi sorteado anteriormente:
        /*
        while(verificaSorteado(vet, i))
        {
            aux = rand() % (n-1);
            vet[i] = aux;
        }
        */
        cout << "AAAAAAAAAAAAAAAAAA" << endl;
        cout << aux << endl;
        // posiciona o cursor no registro aux:
        arqBin.seekg(aux * sizeof(ProductReview));

        // armaneza registro aux no vetor:
        arqBin.read((char *)&reviews[i], sizeof(ProductReview));
    }

    // fecha o arquivo binário:
    arqBin.close();

    return reviews;
}



int main(int argc, char const *argv[])
{   
    if(argc < 2){
        cout << "ERRO: Número de argumentos inválido!" << endl;
        return 0;
    }

    string path = argv[1];

    carregaArquivoPorBlocos(path, MAX);

    cout << "Indique o número de registros que deseja importar: ";
    int n;
    cin >> n;

    // cria vetor de objetos ProductReview com n posições:
    ProductReview *reviews = import(n);

    cout << "Criaremos um arquivo binário com " << n << " registros aleatórios." << endl;

    for (int i = 0; i < n; i++)
    {   
        cout << endl;
        reviews[i].print();
        cout << endl;
    }

    return 0;
}
