#include <iostream>
#include <fstream>
#include "ProductReview.h"

using namespace std;

ProductReview::ProductReview(int registro)
{
    //inicializa variável para ler o arquivo:
    ifstream arq("ratings_Electronics.bin", ios::binary);

    //verifica se o arquivo foi aberto:
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    //posiciona o cursor no início do registro:

    //lê o registro e armazena em userId:

    //lê o registro e armazena em productId:

    //lê o registro e armazena em rating:

    //lê o registro e armazena em timestamp:
}

ProductReview::~ProductReview()
{}

void ProductReview::print()
{
    //converte dados binários para os tipos desejados:
    string auxUserId = reinterpret_cast<string>(this->userId);
    string auxProductId = reinterpret_cast<string>(this->productId);
    float auxRating = reinterpret_cast<float>(this->rating);
    string auxTimestamp = reinterpret_cast<string>(this->timestamp);

    //imprime o conteúdo do registro binário em seus tipos originais:
    cout << "User ID: " << auxUserId << endl;
    cout << "Product ID: " << auxProductId << endl;
    cout << "Rating: " << auxRating << endl;
    cout << "Timestamp: " << auxTimestamp << endl;
}
