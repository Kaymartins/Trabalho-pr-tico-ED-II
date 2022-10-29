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

    //posiciona o cursor no início do registro

    //lê o registro
}

ProductReview::~ProductReview()
{}

void ProductReview::print()
{
    //imprime o conteúdo do registro do arquivo binário:
    cout << "User ID: " << this->userId << endl;
    cout << "Product ID: " << this->productId << endl;
    cout << "Rating: " << this->rating << endl;
    cout << "Timestamp: " << this->timestamp << endl;
}
