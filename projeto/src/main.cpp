#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "../headers/TabelaHash.h"
#include "../headers/ProductReview.h"

using namespace std;

// void ampliaVetor(ProductReview *vet, int *tam)
// {
//     // cria um novo vetor auxiliar com o dobro do tamanho original:
//     auto *aux = new ProductReview[(*tam) * 2];

//     // copia os dados do vetor original para o vetor auxiliar:
//     for (int i = 0; i < *tam; i++)
//     {
//         aux[i] = vet[i];
//     }

//     // libera o espaço de memória do vetor original:
//     delete[] vet;

//     // passa o endereço do vetor auxiliar para o vetor original:
//     vet = aux;

//     // atualiza o tamanho do vetor original:
//     *tam = (*tam) * 2;
// }

// void createBinary(string &path)
// {
//     // abre o arquivo de texto no diretório path:
//     ifstream arq(path);

//     // cria vetor de objetos ProductReview:
//     int tam = 100;
//     ProductReview *reviews = new ProductReview[tam];

//     if (!arq.is_open())
//     {
//         cout << "ERRO: Erro ao abrir o arquivo!" << endl;
//         return;
//     }

//     // lê o arquivo de texto e armazena no vetor de objetos:
//     int i = 0;
//     while (!arq.eof())
//     {
//         if (i == tam)
//         {
//             ampliaVetor(reviews, &tam);
//         }

//         string userId, productId, strRating, timestamp;
//         float rating;

//         // lê cada linha do arquivo de texto e armazena os dados em uma string:
//         getline(arq, userId, ',');
//         getline(arq, productId, ',');
//         getline(arq, strRating, ',');
//         getline(arq, timestamp, '\n');

//         // seta os dados do objeto para ProductReview:
//         reviews[i].setUserId(userId);
//         reviews[i].setProductId(productId);
//         rating = stof(strRating);
//         reviews[i].setRating(rating);
//         reviews[i].setTimestamp(timestamp);
//         // atualiza o contador:
//         i++;
//     }

//     // fecha o arquivo de texto:
//     arq.close();

//     // abre o arquivo binário:
//     ofstream file;
//     file.open("../archive/reviews.bin", ios::binary);

//     if (!file.is_open())
//     {
//         cout << "ERRO: Erro ao abrir o arquivo!" << endl;
//         return;
//     }

//     // escreve o arquivo binário:
//     for (i = 0; i < tam; i++)
//     {
//         file.write((char *)&reviews[i], sizeof(ProductReview));
//     }
// }

// void getReview(int i)
// {
//     // abre o arquivo binário para leitura:
//     ifstream arqBin("../archive/reviews.bin", ios::binary);

//     if (!arqBin.is_open())
//     {
//         cout << "ERRO: Erro ao abrir o arquivo!" << endl;
//         return;
//     }

//     // posiciona o cursor no registro i:
//     arqBin.seekg(i * sizeof(ProductReview));

//     // // lê o registro i:
//     // ProductReview review;
//     // arqBin.read((char *)&review, sizeof(ProductReview));

//     // inicializa variável do tipo ProductReview:
//     ProductReview *review = new ProductReview;

//     // lê o registro i:
//     arqBin.read((char *)review, sizeof(ProductReview));
//     review->print();

//     /*
//     // inicializa variáveis de dados auxiliares:
//     string userId, productId, strRating, timestamp;
//     float rating;

//     // lê cada linha do arquivo de texto e armazena os dados em uma string:
//     getline(arqBin, userId, ',');
//     getline(arqBin, productId, ',');
//     getline(arqBin, strRating, ',');
//     getline(arqBin, timestamp, '\n');

//     // seta os dados do objeto para ProductReview:
//     review.setUserId(userId);
//     review.setProductId(productId);
//     rating = stof(strRating);
//     review.setRating(rating);
//     review.setTimestamp(timestamp);
//     */

//     // fecha o arquivo binário:
//     arqBin.close();

// }

// bool verificaSorteado(int *vet, int i)
// {
//     for (int j = 0; j < i; j++)
//     {
//         if (vet[i] == vet[j]){
//             return true;
//         }
//     }
//     return false;

   
// }

// ProductReview* import(int n)
// {
//     // abre o arquivo binário para leitura:
//     ifstream arqBin("../archive/reviews.bin", ios::binary);

//     if (!arqBin.is_open())
//     {
//         cout << "ERRO: Erro ao abrir o arquivo!" << endl;
//         return NULL;
//     }

//     // cria vetor de objetos ProductReview com n posições:
//     ProductReview *reviews = new ProductReview[n];

//     // cria vetor auxiliar com índices sorteados de 0 a n-1:
//     int *vet = new int[n];

//     // lê o arquivo binário e armazena no vetor aleatório de objetos:
//     for (int i = 0; i < n; i++)
//     {
//         // sorteia um número aleatório entre 0 e n-1:
//         int aux = rand() % (n-1);
//         vet[i] = aux;

//         // verifica se o número sorteado já foi sorteado anteriormente:
//         /*
//         while(verificaSorteado(vet, i))
//         {
//             aux = rand() % (n-1);
//             vet[i] = aux;
//         }
//         */

//         // posiciona o cursor no registro aux:
//         arqBin.seekg(aux * sizeof(ProductReview));

//         // armaneza registro aux no vetor:
//         arqBin.read((char *)&reviews[i], sizeof(ProductReview));
//     }

//     // fecha o arquivo binário:
//     arqBin.close();

//     return reviews;
// }


// typedef struct RegistroHash {
//     string productId;
//     int qtdReviews = 0;
// } RegistroHash;


// //falta tratar colisões e adicionar registros não repetidos:
// RegistroHash* createTable(int n)
// {
//     // cria vetor de objetos RegistroHash com n posições:
//     RegistroHash *table = new RegistroHash[n];

//     // importa n registros aleatórios do arquivo binário:
//     ProductReview *reviews = import(n);
    
//     // atribui valores iniciais para o vetor de objetos RegistroHash:
//     for (int i = 0; i < n; i++)
//     {
//         table[i].productId = reviews[i].getProductId();
//         table[i].qtdReviews += 1;

//         // verifica se o produto já está na tabela:
//         // if(table[i].qtdReviews > 1)
//         // {
//         //     table[i] = rand() % (n-1);
//         // }
//     }

//     return table;
// }

int main(int argc, char const *argv[])
{   
    //Teste da Etapa 1:------------------------------------------
    // if(argc < 2){
    //     cout << "ERRO: Número de argumentos inválido!" << endl;
    //     return 0;
    // }

    // string path = argv[1];

    // createBinary(path);

    // cout << "Indique o número de registros que deseja importar: ";
    // int n;
    // cin >> n;

    // // cria vetor de objetos ProductReview com n posições:
    // ProductReview *reviews = import(n);

    // cout << "Criaremos um arquivo binário com " << n << " registros aleatórios." << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     reviews[i].print();
    // }
    //------------------------------------------------------------

    // Teste da etapa 3--------------------------------

    TabelaHash h(3);
    int arr[] = {2, 4, 6, 8, 10};

    for (int i = 0; i < 5; i++)
    {
        h.inserirItem(arr[i]);
    }
    cout << "Tabela Hash" << endl;
    h.printTable();
    h.pesquisarItem(10);
   

    return 0;
}
