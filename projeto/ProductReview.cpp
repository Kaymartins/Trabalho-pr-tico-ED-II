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
    //imprime o conteúdo do registro:
    cout << "userId: " << this->userId << endl;
    cout << "productId: " << this->productId << endl;
    cout << "rating: " << this->rating << endl;
    cout << "timestamp: " << this->timestamp << endl;
}
