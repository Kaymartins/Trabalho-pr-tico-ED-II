#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cstring>
#include <chrono>

#include "../headers/ProductReview.h"
#include "../headers/TabelaHash.h"
#include "../headers/sorts.h"
#include "../headers/ArvoreVP.h"
#include "../headers/ArvoreB.h"

using namespace std;
using namespace chrono;

default_random_engine gen;

// número de registros do arquivo de entrada:
const int MAX = 7824483;

// cria arquivo binário:
void createBinary(string &path)
{
    // abre arquivo para leitura:
    ifstream arq(path + "/ratings_Electronics.csv");

    // cria vetor de registros ProductReview:
    ProductReview *reviews = new ProductReview[MAX];

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
        file.open(path + "/reviews.bin", ios::binary);
        if (file.is_open())
        {
            // escreve o vetor de registros no arquivo binário:
            for (int i = 0; i < MAX; i++)
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
void getReview(string &path, int i)
{

    // abre o arquivo binário para leitura:
    ifstream arqBin(path + "/reviews.bin", ios::binary);

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

    arqBin.read(reinterpret_cast<char *>(auxUserId), 21);
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

void sort(ProductReview *vet, int n, int methodId, int *metricasOrdenacao)
{
    switch (methodId)
    {
    case 0:
        mergeSort(vet, 0, n - 1, metricasOrdenacao);
        break;
    case 1:
        quickSort(vet, 0, n - 1, metricasOrdenacao);
        break;
    case 2:
        timSort(vet, n, metricasOrdenacao);
        break;
    default:
        cout << "ERRO: Metodo de ordenacao invalido!" << endl;
    }
}

// cria vetor de índices aleatórios:
void shuffle(int *array)
{

    // sortei um número aleatório entre 0 e MAX:
    for (int i = MAX - 1; i > 0; i--)
    {
        // cria uma semente para o gerador de Numeros aleatórios:
        unsigned seed = system_clock::now().time_since_epoch().count();

        // cria um gerador de Numeros aleatórios:
        srand(seed);

        // gera um número aleatório entre 0 e MAX-1:
        int j = rand() % (i + 1);

        // troca os valores do índice i com o índice j:
        int aux = array[j];
        array[j] = array[i];
        array[i] = aux;
    }
}

// gera um vetor com Numeros aleatórios:
int *criaIndices()
{

    // declara vetor de posições:
    // int *Numeros = (int*) malloc((MAX - 1) * sizeof(int));
    int *Numeros = new int[(MAX - 1) * sizeof(int)];

    // inicializa vetor de posições com as posições do arquivo:
    for (int i = 0; i < MAX; i++)
    {
        Numeros[i] = i + 1;
    }

    // reinicializa o vetor com Numeros aleatórios:
    shuffle(Numeros);

    // retorna vetor com Numeros aleatórios:
    return Numeros;
}

// importa n registros aleatórios do arquivo binário:
ProductReview *import(string &path, int n)
{
    // abre o arquivo binário para leitura:
    ifstream arqBin(path + "/reviews.bin", ios::binary);

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

    delete[] aux;

    // fecha o arquivo binário:
    arqBin.close();

    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << duration_cast<duration<double>>(fim - inicio).count() << " segundos para importacao." << endl;

    return reviews;
}

// falta tratar colisões e adicionar registros não repetidos:
void createTable(string &path, int registros)
{
    ProductReview *reviews = import(path, registros);
    TabelaHash *hashTable = new TabelaHash(registros);

    // atribui valores iniciais para o vetor de objetos RegistroHash:
    for (int i = 0; i < registros; i++)
    {
        hashTable->inserirItem(reviews[i].getProductId());
    }

    cout << "Tabela criada com sucesso!" << endl;
    cout << endl;

    int p;
    cout << "Digite a quantidade de produtos mais avaliados que voce deseja visualizar: ";
    cin >> p;

    hashTable->ordenaTabela(p);

    cout << "Ordenacao concluida com sucesso!" << endl;

    delete[] reviews;
    delete hashTable;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "ERRO: Número de argumentos invalido! Passe a path do arquivo na execucao." << endl;
        return 0;
    }

    int sortOrHash;

    // atribui a path passada como argumento a variável path:
    string path = argv[1];

    // chama a função createBinary para criar o arquivo binário

    ifstream verificaBin(path + "/reviews.bin");

    if (verificaBin.is_open())
    {
        int recriarBin;
        cout << "Arquivo binario ja existe!" << endl;
        cout << "Deseja recriar o arquivo binario? (1 - Sim / 0 - Nao)" << endl;
        cin >> recriarBin;

        if (recriarBin)
        {
            createBinary(path);
        }
    }
    else
    {
        createBinary(path);
    }

    cout << "Escolha a etapa a ser executada:" << endl;

    cout << "(1) Ordenacao" << endl;
    cout << "(2) Hashing" << endl;
    cout << "(3) Teste Arvore AB e Arvore B(em construcao)" << endl;
    cin >> sortOrHash;
    cout << endl;

    // Se a opção for 1, chama a função de ordenação
    if (sortOrHash == 1)
    {
        int M = 3;
        int *N;
        // quantidade de cojutos de dados para analise
        int linha = 0;
        ifstream input(path + "/input.dat");
        if (!input.is_open())
        {
            cout << "Erro ao ler o arquivo input.dat!" << endl;
            cout << "Os valores serao escolhidos por padrão." << endl;

            N = new int[5];
            N[0] = 10000;
            N[1] = 50000;
            N[2] = 100000;
            N[3] = 500000;
            N[4] = 1000000;
        }
        else
        {
            while (!input.eof())
            {
                string lixo;
                getline(input, lixo, '\n');
                linha++;
            }

            input.seekg(0);

            N = new int[linha];

            linha = 0;

            while (!input.eof())
            {
                string strLinha;
                getline(input, strLinha, '\n');
                N[linha] = stoi(strLinha);
                linha++;
            }
            input.close();
        }

        ofstream saida(path + "/saida.txt");
        saida << "Resultados de eficiência dos métodos de ordenação:\n"
              << endl;

        double tempo;                           // variável para armazenar o tempo de execução de cada algoritmo
        double tempoMedio = 0;                  // variável para armazenar o tempo médio de execução de cada algoritmo
        int metricasOrdenacao[2];               // vetor para armazenar as métricas de comparação de cada algoritmo
        int metricasOrdenacaoMedia[2] = {0, 0}; // vetor para armazenar as métricas de comparação média de cada algoritmo

        for (int reg = 0; reg < linha; reg++)
        {
            tempoMedio = 0;
            metricasOrdenacaoMedia[0] = 0;
            metricasOrdenacaoMedia[1] = 0;

            saida << "<<-------------------------- Ordenando " << N[reg] << " registros -------------------------->>" << endl;
            saida << endl;

            saida << "<<--------------- MergeSort --------------->>" << endl;
            saida << endl;
            for (int i = 0; i < M; i++)
            { // executa o algoritmo de mergeSort para cada conjunto de

                metricasOrdenacao[0] = 0; // zera o vetor de métricas de comparação
                metricasOrdenacao[1] = 0; // zera o vetor de métricas de troca

                ProductReview *reviews = import(path, N[reg]);

                cout << "Executando MergeSort para " << N[reg] << " registros..." << endl;
                cout << endl;

                high_resolution_clock::time_point inicio = high_resolution_clock::now();

                sort(reviews, N[reg], 0, metricasOrdenacao);
                //mergeSort(reviews, 0, N[reg] - 1, metricasOrdenacao);

                

                high_resolution_clock::time_point fim = high_resolution_clock::now();

                tempo = duration_cast<duration<double>>(fim - inicio).count();

                // Escreve no arquivo de saída os resultados de cada execução
                saida << "Ordenação por MergeSort número " << i + 1 << ":" << endl;
                saida << "Tempo de execução: " << tempo << " segundos" << endl;
                saida << "Número de comparacões: " << metricasOrdenacao[0] << endl;
                saida << "Número de trocas: " << metricasOrdenacao[1] << endl;
                saida << endl;

                // Armazena as métricas de comparação e troca para calcular a média
                tempoMedio += tempo;
                metricasOrdenacaoMedia[0] += metricasOrdenacao[0]; // soma as métricas de comparação
                metricasOrdenacaoMedia[1] += metricasOrdenacao[1]; // soma as métricas de troca

                // Libera Memória
                delete[] reviews;
            }

            // Calcula a média das métricas de comparação e troca
            tempoMedio /= M;                // calcula a média do tempo de execução
            metricasOrdenacaoMedia[0] /= M; // calcula a média das métricas de comparação
            metricasOrdenacaoMedia[1] /= M; // calcula a média das métricas de troca

            // Escreve o arquivo de saída com metricas calculadas
            saida << "Desempenho médio do MergeSort:" << endl;
            saida << "Tempo médio de execução do Merge Sort: " << tempoMedio << " segundos" << endl;
            saida << "Número médio de comparações do Merge Sort: " << metricasOrdenacaoMedia[0] << endl;
            saida << "Número médio de trocas do Merge Sort: " << metricasOrdenacaoMedia[1] << endl;
            saida << endl;
            saida << endl;

            tempoMedio = 0;                // calcula a média do tempo de execução
            metricasOrdenacaoMedia[0] = 0; // calcula a média das métricas de comparação
            metricasOrdenacaoMedia[1] = 0; // calcula a média das métricas de troca

            saida << "<<--------------- QuickSort --------------->>" << endl;
            saida << endl;

            for (int i = 0; i < M; i++)
            { // executa o algoritmo de quickSort para cada conjunto de dados

                metricasOrdenacao[0] = 0; // zera o vetor de métricas de comparação
                metricasOrdenacao[1] = 0; // zera o vetor de métricas de troca

                ProductReview *reviews = import(path, N[reg]);

                cout << "Executando QuickSort para " << N[reg] << " registros..." << endl;
                cout << endl;

                high_resolution_clock::time_point inicio = high_resolution_clock::now();

                sort(reviews, N[reg], 1, metricasOrdenacao);
                //quickSort(reviews, 0, N[reg] - 1, metricasOrdenacao);

                high_resolution_clock::time_point fim = high_resolution_clock::now();

                tempo = duration_cast<duration<double>>(fim - inicio).count();

                // Escreve no arquivo de saída os resultados de cada execução
                saida << "Ordenação por QuickSort número " << i + 1 << ":" << endl;
                saida << "Tempo de execução: " << tempo << " segundos" << endl;
                saida << "Número de comparacões: " << metricasOrdenacao[0] << endl;
                saida << "Número de trocas: " << metricasOrdenacao[1] << endl;
                saida << endl;

                // Armazena as métricas de comparação e troca para calcular a média
                tempoMedio += tempo;
                metricasOrdenacaoMedia[0] += metricasOrdenacao[0]; // soma as métricas de comparação
                metricasOrdenacaoMedia[1] += metricasOrdenacao[1]; // soma as métricas de troca

                delete[] reviews;
            }

            // Calcula a média das métricas de comparação e troca
            tempoMedio /= M;                // calcula a média do tempo de execução
            metricasOrdenacaoMedia[0] /= M; // calcula a média das métricas de comparação
            metricasOrdenacaoMedia[1] /= M; // calcula a média das métricas de troca

            // Escreve o arquivo de saída com metricas calculadas
            saida << "Desempenho médio do QuickSort:" << endl;
            saida << "Tempo médio de execução do Quick Sort: " << tempoMedio << " segundos" << endl;
            saida << "Número médio de comparações do Quick Sort: " << metricasOrdenacaoMedia[0] << endl;
            saida << "Número médio de trocas do Quick Sort: " << metricasOrdenacaoMedia[1] << endl;
            saida << endl;
            saida << endl;

            tempoMedio = 0;                // calcula a média do tempo de execução
            metricasOrdenacaoMedia[0] = 0; // zera o vetor de métricas de comparação
            metricasOrdenacaoMedia[1] = 0; // zera o vetor de métricas de troca

            saida << "<<--------------- TimSort --------------->>" << endl;
            saida << endl;

            for (int i = 0; i < M; i++)
            { // executa o algoritmo de countSort para cada conjunto de dados

                metricasOrdenacao[0] = 0; // zera o vetor de métricas de comparação
                metricasOrdenacao[1] = 0; // zera o vetor de métricas de troca

                ProductReview *reviews = import(path, N[reg]);

                cout << "Executando TimSort para " << N[reg] << " registros..." << endl;
                cout << endl;

                high_resolution_clock::time_point inicio = high_resolution_clock::now();

                sort(reviews, N[reg], 2, metricasOrdenacao);
                //timSort(reviews, N[reg], metricasOrdenacao);

                high_resolution_clock::time_point fim = high_resolution_clock::now();

                tempo = duration_cast<duration<double>>(fim - inicio).count();

                // Escreve no arquivo de saída os resultados de cada execução
                saida << "Ordenação por TimSort número " << i + 1 << ":" << endl;
                saida << "Tempo de execução: " << tempo << " segundos" << endl;
                saida << "Número de comparacões: " << metricasOrdenacao[0] << endl;
                saida << "Número de trocas: " << metricasOrdenacao[1] << endl;
                saida << endl;

                // Armazena as métricas de comparação e troca para calcular a média
                tempoMedio += tempo;
                metricasOrdenacaoMedia[0] += metricasOrdenacao[0]; // soma as métricas de comparação
                metricasOrdenacaoMedia[1] += metricasOrdenacao[1]; // soma as métricas de troca

                delete[] reviews;
            }

            // Calcula a média das métricas de comparação e troca
            tempoMedio /= M;                // calcula a média do tempo de execução
            metricasOrdenacaoMedia[0] /= M; // calcula a média das métricas de comparação
            metricasOrdenacaoMedia[1] /= M; // calcula a média das métricas de troca

            // Escreve o arquivo de saída com metricas calculadas
            saida << "Desempenho médio do TimSort:" << endl;
            saida << "Tempo médio de execução do Tim Sort: " << tempoMedio << " segundos" << endl;
            saida << "Número médio de comparações do Tim Sort: " << metricasOrdenacaoMedia[0] << endl;
            saida << "Número médio de trocas do Tim Sort: " << metricasOrdenacaoMedia[1] << endl;
            saida << endl;
        }



        saida.close();

        cout << "Arquivo de saida com dados sobre os metodos de ordenacao gerado com sucesso!" << endl;
    }
    else if (sortOrHash == 2)
    {
        cout << "Indique o numero de registros que deseja importar: ";
        int n;
        cin >> n;

        cout << "Importaremos " << n << " registros aleatorios." << endl;

        createTable(path, n);

        return 0;
    }
    else if (sortOrHash == 3)
    {
        cout << "Indique o numero de registros que deseja importar: ";
        int n;
        cin >> n;

        cout << "Importaremos " << n << " registros aleatorios." << endl;
        ProductReview *reviews = import(path, n);
        ArvoreVP *arvoreVP = new ArvoreVP();
        ArvoreB *arvoreB = new ArvoreB();

        for(int i=0; i<n; i++)
        {
            arvoreVP->insere(&reviews[i]);
        }

        

        cout << "Arvore VP criada com sucesso!" << endl;
        arvoreVP->imprimir();

        cout << "n : " << n << endl;

        for(int i=0; i<n; i++)
        {
            arvoreB->insere(&reviews[i]);
        }

        cout << "Arvore B criada com sucesso!" << endl;
       
        arvoreB->print();
        

        /*
        cout << "Indique o numero de registros que deseja pesquisar na Arvore :" << endl;
        cin >> n;
        ProductReview *reviewsPesquisa = import(path, n);
        ProductReview *resultados = new ProductReview[n];

        for(int i=0; i<n; i++)
        {
            ProductReview *aux;
            aux = arvoreVP->busca(reviewsPesquisa->getUserId(), reviewsPesquisa->getProductId());
            
            if(aux != NULL)
            {
                resultados[i] = *aux;
                cout << "Registro encontrado!" << endl;
                
            }else{
                resultados[i] = ProductReview();
                resultados[i].setProductId("");
                resultados[i].setUserId("");
                resultados[i].setRating(0);
                resultados[i].setTimestamp("");
            }

            delete aux;
        }

    /*
        for(int i=0; i<n; i++)
        {
            cout << "Registro encontrado!" << endl;
            cout << "UserId: " << resultados[i].getUserId() << endl;
            cout << "ProductId: " << resultados[i].getProductId() << endl;
            cout << "Rating: " << resultados[i].getRating() << endl;
            cout << "Timestamp: " << resultados[i].getTimestamp() << endl;
            cout << endl;
        }
    

        delete[] reviewsPesquisa;
        delete[] resultados;
    */
        delete arvoreB;
        delete arvoreVP;

    }
    else
    {
        cout << "Opcao invalida!" << endl;
        cout << "Fechando do Programa" << endl;
    }
}
