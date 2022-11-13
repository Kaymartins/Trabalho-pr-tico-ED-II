#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstring>
#include <chrono>


#include "../headers/TabelaHash.h"
#include "../headers/ProductReview.h"


using namespace std;
using namespace std::chrono;

default_random_engine gen;

const int MAX = 7824483;

/*
void createBinary(string &path, int tamBloco)
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
            
            string userId, productId, timestamp, strRating;

            getline(arq,userId,',');
            getline(arq,productId,',');
            getline(arq,strRating,',');
            getline(arq,timestamp,'\n');

            // seta os dados do objeto para ProductReview:
            float rating;
            reviews[i].setUserId(userId);
            reviews[i].setProductId(productId);
            rating = strtof(strRating.c_str(),nullptr);
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
                
                string userId = reviews[i].getUserId();
                string productId = reviews[i].getProductId();
                float rating = reviews[i].getRating();
                string timestamp = reviews[i].getTimestamp();

                file.write(reinterpret_cast<const char*>(userId.c_str()),21);
                file.write(reinterpret_cast<const char*>(productId.c_str()),10);
                file.write(reinterpret_cast<const char*>(&rating), sizeof(float));
                file.write(reinterpret_cast<const char*>(timestamp.c_str()),10);

            }
        }


        file.close();
        
        cout << "Arquivo binario criado com sucesso!" << endl;
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
    }    

    arq.close();
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

    string userId, productId, timestamp;
    float rating;

    // posiciona o cursor no registro i:
    arqBin.seekg(i * (21 + 10 + sizeof(float) + 10), ios::beg);

    char *auxUserId = new char[21];
    char *auxProductId = new char[10];
    char *auxTimestamp = new char[10];
    auxUserId[21] = '\0';
    auxProductId[10] = '\0';
    auxTimestamp[10] = '\0';


    // inicializa variável do tipo ProductReview:
    ProductReview *review = new ProductReview;

    arqBin.read(reinterpret_cast<char*>(auxUserId), 21);
    arqBin.read(reinterpret_cast<char*>(auxProductId), 10);
    arqBin.read(reinterpret_cast<char*>(&rating), sizeof(float));
    arqBin.read(reinterpret_cast<char*>(auxTimestamp), 10);

    
    userId = auxUserId;
    productId = auxProductId;
    timestamp = auxTimestamp;

    review->setUserId(userId);
    review->setProductId(productId);
    review->setRating(rating);
    review->setTimestamp(timestamp);

    review->print();

    arqBin.close();

    delete [] auxUserId;
    delete [] auxProductId;
    delete [] auxTimestamp;
    delete review;
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

    cout << "Importando " << n << " registros..." << endl;
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

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
        

        // posiciona o cursor no registro aux:
        arqBin.seekg(aux * (21 + 10 + sizeof(float) + 10), ios::beg);

        char *auxUserId = new char[21];
        char *auxProductId = new char[10];
        char *auxTimestamp = new char[10];
        auxUserId[21] = '\0';
        auxProductId[10] = '\0';
        auxTimestamp[10] = '\0';
        float rating;


        arqBin.read(reinterpret_cast<char*>(auxUserId), 21);
        arqBin.read(reinterpret_cast<char*>(auxProductId), 10);
        arqBin.read(reinterpret_cast<char*>(&rating), sizeof(float));
        arqBin.read(reinterpret_cast<char*>(auxTimestamp), 10);

        string userId = auxUserId;
        string productId = auxProductId;
        string timestamp = auxTimestamp;

        reviews[i].setUserId(userId);
        reviews[i].setProductId(productId);
        reviews[i].setRating(rating);
        reviews[i].setTimestamp(timestamp);

    } 

    // fecha o arquivo binário:
    arqBin.close();

    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;

    return reviews;
}
*/

int main(int argc, char const *argv[])
{   

/*
    if(argc < 2){
        cout << "ERRO: Número de argumentos inválido!" << endl;
        return 0;
    }

    string path = argv[1];

    createBinary(path, MAX);

    getReview(5);

    cout << "Indique o numero de registros que deseja importar: ";
    int n;
    cin >> n;

    // cria vetor de objetos ProductReview com n posições:
    ProductReview *reviews = import(n);
    cout << "Importação realizada com sucesso!" << endl;

    cout << "Criaremos um arquivo binário com " << n << " registros aleatórios." << endl;

    
    for (int i = 0; i < 10; i++)
    {   
        cout << endl;
        reviews[i].print();
        cout << endl;
    }
*/
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
