#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstring>
#include <chrono>

#include "../headers/ProductReview.h"
#include "../headers/sorts.h"


using namespace std;
using namespace chrono;

default_random_engine gen;

// número de registros do arquivo de entrada:
const int MAX = 7824483;

// cria arquivo binário:
void createBinary(string &path, int tamBloco)
{

    // abre arquivo para leitura:
    ifstream arq(path);

    // cria vetor de registros ProductReview:
    ProductReview *reviews = new ProductReview[tamBloco];

    if (arq.is_open())
    {
        cout << "Criando arquivo binario ... " << endl;

        // inicia contagem de tempo:
        high_resolution_clock::time_point inicio = high_resolution_clock::now();

        // lê todos os registros do arquivo de entrada:
        int i = 0;
        while (!arq.eof())
        {
            // declara variáveis auxiliares:
            string userId, productId, timestamp, strRating;

            // captura os dados objeto ProductReview:
            getline(arq, userId, ',');
            getline(arq, productId, ',');
            getline(arq, strRating, ',');
            getline(arq, timestamp, '\n');

            // seta os dados do objeto para o vetor de registros:
            float rating;
            reviews[i].setUserId(userId);
            reviews[i].setProductId(productId);
            rating = strtof(strRating.c_str(), nullptr);
            reviews[i].setRating(rating);
            reviews[i].setTimestamp(timestamp);

            i++;
        }

        // abre arquivo binário para escrita:
        ofstream file;
        file.open("../archive/reviews.bin", ios::binary);
        if (file.is_open())
        {
            // escreve o vetor de registros no arquivo binário:
            for (int i = 0; i < tamBloco; i++)
            {
                // inicializa variáveis auxiliares:
                string userId = reviews[i].getUserId();
                string productId = reviews[i].getProductId();
                float rating = reviews[i].getRating();
                string timestamp = reviews[i].getTimestamp();

                // escreve os dados do objeto no arquivo binário:
                file.write(reinterpret_cast<const char *>(userId.c_str()), 21);
                file.write(reinterpret_cast<const char *>(productId.c_str()), 10);
                file.write(reinterpret_cast<const char *>(&rating), sizeof(float));
                file.write(reinterpret_cast<const char *>(timestamp.c_str()), 10);
            }
        }

        // fecha arquivo binário:
        file.close();
        cout << "Arquivo binario criado com sucesso!" << endl;

        // finaliza contagem de tempo:
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
    }

    // fecha arquivo de entrada:
    arq.close();
}

// retorna um registro de índice i:
void getReview(int i)
{

    // abre o arquivo binário para leitura:
    ifstream arqBin("../archive/reviews.bin", ios::binary);

    if (!arqBin.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo! Nao foi possivel buscar o registro." << endl;
        return;
    }

    // declara variáveis auxiliares:
    string userId, productId, timestamp;
    float rating;

    // posiciona o cursor no registro i:
    arqBin.seekg(i * (21 + 10 + sizeof(float) + 10), ios::beg);

    // declara vetores auxiliares de char para armazenar os dados do registro:
    char *auxUserId = new char[21];
    char *auxProductId = new char[10];
    char *auxTimestamp = new char[10];
    // define final dos vetores de char:
    auxUserId[21] = '\0';
    auxProductId[10] = '\0';
    auxTimestamp[10] = '\0';

    // inicializa variável do tipo ProductReview:
    ProductReview *review = new ProductReview;

    // lê os dados do registro i:
    arqBin.read(reinterpret_cast<char *>(auxUserId), 21);
    arqBin.read(reinterpret_cast<char *>(auxProductId), 10);
    arqBin.read(reinterpret_cast<char *>(&rating), sizeof(float));
    arqBin.read(reinterpret_cast<char *>(auxTimestamp), 10);

    // inicializa as variáveis auxiliares com os dados do registro i:
    userId = auxUserId;
    productId = auxProductId;
    timestamp = auxTimestamp;

    // seta os dados para o registro ProductReview:
    review->setUserId(userId);
    review->setProductId(productId);
    review->setRating(rating);
    review->setTimestamp(timestamp);

    // imprime os dados do registro:
    review->print();

    // fecha arquivo binário:
    arqBin.close();

    // libera memória alocada:
    delete[] auxUserId;
    delete[] auxProductId;
    delete[] auxTimestamp;
    delete review;
}

// cria vetor de índices aleatórios:
void shuffle(int *array)
{

    // sortei um número aleatório entre 0 e MAX:
    for (int i = MAX - 1; i > 0; i--)
    {
        // cria uma semente para o gerador de números aleatórios:
        unsigned seed = system_clock::now().time_since_epoch().count();

        // cria um gerador de números aleatórios:
        srand(seed);

        // gera um número aleatório entre 0 e MAX-1:
        int j = rand() % (i + 1);

        // troca os valores do índice i com o índice j:
        int aux = array[j];
        array[j] = array[i];
        array[i] = aux;
    }
}

// gera um vetor com números aleatórios:
int *criaIndices()
{

    // declara vetor de posições:
    // int *numeros = (int*) malloc((MAX - 1) * sizeof(int));
    int *numeros = new int[(MAX - 1) * sizeof(int)];

    // inicializa vetor de posições com as posições do arquivo:
    for (int i = 0; i < MAX; i++)
    {
        numeros[i] = i + 1;
    }

    // reinicializa o vetor com números aleatórios:
    shuffle(numeros);

    // retorna vetor com números aleatórios:
    return numeros;
}

// importa n registros aleatórios do arquivo binário:
ProductReview *import(int n)
{

    // abre o arquivo binário para leitura:
    ifstream arqBin("../archive/reviews.bin", ios::binary);

    if (!arqBin.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo! Nao foi possivel importar os registros." << endl;
        return NULL;
    }

    cout << "Importando " << n << " registros..." << endl;
    // inicializa contagem de tempo:
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    // cria vetor de objetos ProductReview com n posições:
    ProductReview *reviews = new ProductReview[n];

    // cria vetor auxiliar com índices sorteados de 0 a MAX-1:
    int *aux = criaIndices();

    // importa n registros aleatórios:
    for (int i = 0; i < n; i++)
    {
        // captura índice aleatório contido no vetor auxiliar:
        int random = aux[i];

        // posiciona o cursor no registro aleatório:
        arqBin.seekg(random * (21 + 10 + sizeof(float) + 10), ios::beg);

        // declara vetores auxiliares de char para armazenar os dados do registro:
        char *auxUserId = new char[21];
        char *auxProductId = new char[10];
        char *auxTimestamp = new char[10];
        // define final dos vetores de char:
        auxUserId[21] = '\0';
        auxProductId[10] = '\0';
        auxTimestamp[10] = '\0';
        // declara variável auxiliar:
        float rating;

        // lê os dados do registro:
        arqBin.read(reinterpret_cast<char *>(auxUserId), 21);
        arqBin.read(reinterpret_cast<char *>(auxProductId), 10);
        arqBin.read(reinterpret_cast<char *>(&rating), sizeof(float));
        arqBin.read(reinterpret_cast<char *>(auxTimestamp), 10);

        // inicializa as variáveis auxiliares com os dados do registro:
        string userId = auxUserId;
        string productId = auxProductId;
        string timestamp = auxTimestamp;

        // seta os dados para o registro ProductReview:
        reviews[i].setUserId(userId);
        reviews[i].setProductId(productId);
        reviews[i].setRating(rating);
        reviews[i].setTimestamp(timestamp);

        // libera memória alocada:
        delete[] auxUserId;
        delete[] auxProductId;
        delete[] auxTimestamp;

    }

    // fecha o arquivo binário:
    arqBin.close();

    // finaliza contagem de tempo:
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;

    // retorna vetor de registros ProductReview:
    return reviews;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "ERRO: Numero de argumentos invalido! Passe a path do arquivo na execucao." << endl;
        return 0;
    }

    int sortOrHash;

    // atribui a path passada como argumento a variável path:
    string path = argv[1];

    //chama a função createBinary para criar o arquivo binário
    createBinary(path, MAX);
    
    cout << "Escolha a etapa a ser executada:" << endl;

    cout << "(1) Ordenacao" << endl;
    cout << "(2) Hashing" << endl;
    cin >> sortOrHash;
    cout << endl;

    
    //Se a opção for 1, chama a função de ordenação
    if(sortOrHash == 1){
        int M = 3; //quantidade de cojutos de dados para analise
        int N[5] = {10000, 50000, 100000, 500000, 1000000}; //quantidade de dados para analise

        double tempo[3] = {0, 0, 0}; //vetor para armazenar o tempo de execução de cada algoritmo
        int metricasOrdenacao[2] = {0, 0}; //vetor para armazenar as métricas de comparação de cada algoritmo

        for(int i = 0; i < M; i++){ //executa o algoritmo de mergeSort para cada conjunto de 
            ProductReview *reviews = import(1000000);

            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            mergeSort(reviews, 0, N[4] - 1, metricasOrdenacao);            
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            
            cout << "Tempo de execucao do MergeSort: " << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
            tempo[0] += duration_cast<duration<double>>(fim - inicio).count();

            cout << "Numero de comparacoes do MergeSort: " << metricasOrdenacao[0] << " comparacoes" << endl;
            cout << "Numero de trocas do MergeSort: " << metricasOrdenacao[1] << " movimentacoes" << endl;
            cout << endl;

            //Escreve o arquivo de saída com metricas calculadas

            delete[] reviews;
        }
        tempo[0] /= M; //calcula a média do tempo de execução do algoritmo de mergeSort

        metricasOrdenacao[0] = 0; //zera o vetor de métricas de comparação
        metricasOrdenacao[1] = 0; //zera o vetor de métricas de troca

        for(int i = 0; i < M; i++){ //executa o algoritmo de quickSort para cada conjunto de dados
            ProductReview *reviews = import(1000000);

            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            quickSort(reviews, 0, N[4] - 1, metricasOrdenacao);
            high_resolution_clock::time_point fim = high_resolution_clock::now();

            cout << "Tempo de execucao do QuickSort: " << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
            tempo[1] += duration_cast<duration<double>>(fim - inicio).count();

            cout << "Numero de comparacoes do QuickSort: " << metricasOrdenacao[0] << " comparacoes" << endl;
            cout << "Numero de trocas do QuickSort: " << metricasOrdenacao[1] << " movimentacoes" << endl;
            cout << endl;

            //Escreve o arquivo de saída com metricas calculadas

            delete[] reviews;
        }
        tempo[1] /= M; //calcula a média do tempo de execução do algoritmo de quickSort

        // for(int i = 0; i < M; i++){ //executa o algoritmo de countSort para cada conjunto de dados
        //     ProductReview *reviews = import(1000000);
        //     high_resolution_clock::time_point inicio = high_resolution_clock::now();
        //     //terceiroSort(reviews, N[i]);           
        //     high_resolution_clock::time_point fim = high_resolution_clock::now();
        //     tempo[2] += duration_cast<duration<double>>(fim - inicio).count();
        //     delete[] reviews;
        // }
        // tempo[2] /= M; //calcula a média do tempo de execução do algoritmo de countSort

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