#include <iostream>
#include <fstream>
#include "ProductReview.h"

using namespace std;

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
    ofstream arqBin("path/ratings_Electronics.bin", ios::binary);

    if (!arqBin.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo!" << endl;
        return;
    }

    // escreve o arquivo binário:
    for (i = 0; i < 100; i++)
    {
        if (i == tam - 1)
            arqBin.write((char *)&reviews[i], sizeof(ProductReview));
    }
}

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

void getReview(int i)
{
    // abre o arquivo binário para leitura:
    ifstream arqBin("path/ratings_Electronics.bin", ios::binary);

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
    ProductReview review;

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

    // fecha o arquivo binário:
    arqBin.close();

    // imprime o conteúdo do registro:
    review.print();
}

int main()
{
    cout << "Hello World";

    return 0;
}
