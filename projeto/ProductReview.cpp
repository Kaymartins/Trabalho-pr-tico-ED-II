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

    //transforma userId binário em string:

    //transforma productId binário em inteiro:

    //transforma rating binário em float:

    //transforma timestamp binário em inteiro:

    //imprime o conteúdo do registro do arquivo binário em texto:
    cout << "User ID: " << this->userId << endl;
    cout << "Product ID: " << this->productId << endl;
    cout << "Rating: " << this->rating << endl;
    cout << "Timestamp: " << this->timestamp << endl;
}
