#include <iostream>
#include <fstream>
#include "ProductReview.h"

using namespace std;


void createBinary(string& path)
{
    //abre o arquivo de texto no diretório path:
    ifstream arq(path);

    //cria vetor de objetos ProductReview:
    ProductReview *reviews = new ProductReview[100];

    if(!arq.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo!" << endl;
        return;
    }

    //lê o arquivo de texto e armazena no vetor de objetos:
    int i = 0;
    while(!arq.eof())
    {
        string userId, productId, strRating, timestamp;
        float rating;

        //lê cada linha do arquivo de texto e armazena os dados em uma string:
        getline(arq, userId, ',');
        getline(arq, productId, ',');
        getline(arq, strRating, ',');
        getline(arq, timestamp, '\n');

        //seta os dados do objeto para ProductReview:
        reviews[i].setUserId(userId);
        reviews[i].setProductId(productId);
        rating = stof(strRating);
        reviews[i].setRating(rating);
        reviews[i].setTimestamp(timestamp);
        
        //atualiza o contador:
        i++;
    }

    //fecha o arquivo de texto:
    arq.close();

    //abre o arquivo binário:
    ofstream arqBin("arquive/ratings_Electronics.bin", ios::binary);

    if(!arqBin.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo!" << endl;
        return;
    }

    //escreve o arquivo binário:
    for(i = 0; i < 100; i++)
    {
        arqBin.write((char*)&reviews[i], sizeof(ProductReview));
    }
}

int main()
{
    cout<<"Hello World";

    return 0;
}


