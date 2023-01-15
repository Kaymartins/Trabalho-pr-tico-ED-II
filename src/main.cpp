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
#include "../headers/Huffman.h"
#include "../headers/LZW.h"

using namespace std;
using namespace chrono;

default_random_engine gen;

// número de registros do arquivo de entrada:
const int MAX = 7824483;

string globalPath;
unordered_map<char, string> codigo;


// cria arquivo binário:
void createBinary(string &path)
{
    globalPath = path;
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
void getReview(int i)
{

    // abre o arquivo binário para leitura:
    ifstream arqBin(globalPath + "/reviews.bin", ios::binary);

    if (!arqBin.is_open())
    {
        cout << "ERRO: Erro ao abrir o arquivo! Nao foi possivel buscar o registro." << endl;
        return;
    }

    // inicializa variável do tipo ProductReview:
    ProductReview *review = new ProductReview;

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
        review->setUserId(userId);
        review->setProductId(productId);
        review->setRating(rating);
        review->setTimestamp(timestamp);

        // imprime os dados do registro:
        review->print();

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
ProductReview *import(int n)
{
    // abre o arquivo binário para leitura:
    ifstream arqBin(globalPath + "/reviews.bin", ios::binary);

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

string comprime(string s, int method)
{
    string comprime = "";
    if(method == 0)
    {   
        Huffman* h = new Huffman();
        comprime = h->comprime(s);
        codigo = h->getCodigo();
        return comprime;
    }else if(method == 1){
        //LZ77* lz77 = new LZ77();
        //comprime = lz77->comprime(s);
        //codigo = lz77->getCodigo();
    }else if(method == 2) {
        LZW* lzw = new LZW();
        //comprime = lzw->comprime(s);
        //codigo = lzw->getCodigo();
        return comprime;
    }
    return comprime;
}

void comprime(int metodo)
{
    string texto, comprimido;
    ifstream file(globalPath + "/reviewsOrig.txt"); // abre o arquivo

    if (file.is_open()) { // verifica se o arquivo foi aberto corretamente
        string line;
        while (getline(file, line)) { // lê cada linha do arquivo
            texto += line; // adiciona a linha lida à string
        }
        file.close(); // fecha o arquivo

        switch(metodo)
        {
            case 0: 
                cout << "=== Teste Huffman ===" << endl << endl; 
                cout << "Texto original do arquivo : " << texto << endl;
                comprimido = comprime(texto, 0);
                cout << "Texto comprimido : " << comprimido << endl;
                break;
        }

        ofstream file2(globalPath + "/reviewsComp.bin" , ios::binary);
        if(file2.is_open())
        {
            file2 << comprimido;
            file2.close();
        }else{
            cout << "Erro ao abrir o arquivo 2." << endl;
        }
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

string descomprime(string s, int method)
{
    string descomprime = "";
    if(method == 0)
    {   
        Huffman* h = new Huffman();
        descomprime = h->descomprime(s, codigo);
        return descomprime;
    }else{
        return descomprime;
    }
}

void descomprime(int metodo)
{
    string texto, descomprimido;
    ifstream file(globalPath + "/reviewsComp.bin", ios::binary); // abre o arquivo
    
    if(file.is_open()){
        string line;
        while (getline(file, line)) { // lê cada linha do arquivo
            texto += line; // adiciona a linha lida à string
        }
        file.close(); // fecha o arquivo

        switch(metodo)
        {
            case 0: 
                cout << "=== Teste Huffman ===" << endl << endl; 
                cout << "Texto comprimido do arquivo : " << texto << endl;
                descomprimido = descomprime(texto, 0);
                cout << "Texto descomprimido : " << descomprimido << endl;
                break;
        }

        ofstream file2(globalPath + "/reviewsDesc.txt");
        if(file2.is_open())
        {
            file2 << descomprimido;
            file2.close();
        }else{
            cout << "Erro ao abrir o arquivo 2." << endl;
        }
    }else{
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

void metricasOrdenacao()
{
    int M = 3;
        int *N;
        // quantidade de cojutos de dados para analise
        int linha = 0;
        ifstream input(globalPath + "/input.dat");
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

        ofstream saida(globalPath + "/saida.txt");
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

                ProductReview *reviews = import(N[reg]);

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

                ProductReview *reviews = import(N[reg]);

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

                ProductReview *reviews = import(N[reg]);

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

void metricasEstruturasBalanceadas()
{
    cout << "Inicializando contabilizacao de metricas de execução da arvore VP e da arvore B" << endl;
    int m = 3;
    int p = 1000000;
    int b = 300;
    int metricasComparacaoArvoreVP[m];
    double metricasTempoArvoreVP[m];
    int metricasComparacaoArvoreB[m];
    double metricasTempoArvoreB[m];
    int metricasComparacaoArvoreB2[m];
    double metricasTempoArvoreB2[m];

    ofstream saida(globalPath + "/saida.txt");

            
            for(int i = 0; i < m; i++)
            {
                
                saida << "<<-------------------------- Executando " << i + 1 << " metrica -------------------------->>" << endl;
                saida << "Importaremos " << p << " registros aleatorios." << endl;
                ProductReview *reviews = import(p);
                ArvoreVP *arvoreVP = new ArvoreVP();
                ArvoreB *arvoreB = new ArvoreB();
                ArvoreB *arvoreB2 = new ArvoreB();

                

                saida << "VAMOS CRIAR AS METRICAS DA ARVORE VP" << endl;

                high_resolution_clock::time_point start = high_resolution_clock::now();
                for(int j=0; j<p; j++)
                {
                    arvoreVP->insere(&reviews[j]);
                }
                high_resolution_clock::time_point end = high_resolution_clock::now();
                metricasTempoArvoreVP[i] = duration_cast<duration<double>>(end - start).count();

                ProductReview *reviewsBusca = import(b);

                start = high_resolution_clock::now();
                for(int j=0; j<b; j++)
                {
                    ProductReview review = reviewsBusca[j];
                    arvoreVP->busca(review.getUserId(), review.getProductId());
                }
                end = high_resolution_clock::now();

                metricasTempoArvoreVP[i] += duration_cast<duration<double>>(end - start).count();

                saida << "METRICAS " << i << " DA ARVORE VP CRIADAS : " << endl;
                saida << "Numero de comparacoes : " << arvoreVP->getComparacoes() << endl;
                saida << "Tempo : " << metricasTempoArvoreVP[i] << endl;
                metricasComparacaoArvoreVP[i] = arvoreVP->getComparacoes();

                saida << "VAMOS CRIAR AS METRICAS DA ARVORE B COM M =  20 " << endl;
                arvoreB->setT(20);
                start = high_resolution_clock::now();
                for(int j=0; j<p; j++)
                {
                    arvoreB->insere(&reviews[j]);
                }
                end = high_resolution_clock::now();
                metricasTempoArvoreB[i] = duration_cast<duration<double>>(end - start).count();

                start = high_resolution_clock::now();
                for(int j=0; j<b; j++)
                {
                    ProductReview review = reviewsBusca[j];
                    arvoreB->busca(review.getUserId(), review.getProductId());
                }
                end = high_resolution_clock::now();

                metricasTempoArvoreB[i] += duration_cast<duration<double>>(end - start).count();

                metricasComparacaoArvoreB[i] = arvoreB->getComparacoes();

                saida << "METRICAS" << i << " DA ARVORE B COM M = 20 CRIADAS : " << endl;
                saida << "Numero de comparacoes : " << arvoreB->getComparacoes() << endl;
                saida << "Tempo : " << metricasTempoArvoreB[i] << endl;
                metricasComparacaoArvoreB[i] = arvoreB->getComparacoes();

                saida << "VAMOS CRIAR AS METRICAS DA ARVORE B COM M =  200 " << endl;
                arvoreB2->setT(200);
                start = high_resolution_clock::now();
                for(int j=0; j<p; j++)
                {
                    arvoreB2->insere(&reviews[j]);
                }
                
                end = high_resolution_clock::now();
                metricasTempoArvoreB2[i] = duration_cast<duration<double>>(end - start).count();

                start = high_resolution_clock::now();
                for(int j=0; j<b; j++)
                {
                    ProductReview review = reviewsBusca[j];
                    arvoreB2->busca(review.getUserId(), review.getProductId());
                }
                end = high_resolution_clock::now();

                metricasTempoArvoreB2[i] += duration_cast<duration<double>>(end - start).count();

                saida << "METRICAS TOTAIS" << i << " DA ARVORE B COM M = 200 CRIADAS : " << endl;
                saida << "Numero de comparacoes : " << arvoreB2->getComparacoes() << endl;
                saida << "Tempo : " << metricasTempoArvoreB2[i] << endl;
                metricasComparacaoArvoreB2[i] = arvoreB2->getComparacoes();

                delete arvoreVP;
                delete arvoreB;
                delete arvoreB2;
                delete[] reviews;
                delete[] reviewsBusca;
            }



            double mediaComparacoesArvoreVP = 0;
            double mediaTempoArvoreVP = 0;
            double mediaComparacoesArvoreB = 0;
            double mediaTempoArvoreB = 0;
            double mediaComparacoesArvoreB2 = 0;
            double mediaTempoArvoreB2 = 0;

            for(int i = 0; i < m; i++)
            {
                mediaComparacoesArvoreVP += metricasComparacaoArvoreVP[i];
                mediaTempoArvoreVP += metricasTempoArvoreVP[i];
                mediaComparacoesArvoreB += metricasComparacaoArvoreB[i];
                mediaTempoArvoreB += metricasTempoArvoreB[i];
                mediaComparacoesArvoreB2 += metricasComparacaoArvoreB2[i];
                mediaTempoArvoreB2 += metricasTempoArvoreB2[i];
            }
            mediaComparacoesArvoreVP /= m;
            mediaTempoArvoreVP /= m;
            mediaComparacoesArvoreB /= m;
            mediaTempoArvoreB /= m;
            mediaComparacoesArvoreB2 /= m;
            mediaTempoArvoreB2 /= m;

            saida << "MÉDIA FINAL ARVORE VP :" << endl;
            saida << "Numero de comparacoes : " << mediaComparacoesArvoreVP << endl;
            saida << "Tempo: " << mediaTempoArvoreVP << endl;

            saida << "MÉDIA FINAL ARVORE B COM M = 20:" << endl;
            saida << "Numero de comparacoes : " << mediaComparacoesArvoreB << endl;
            saida << "Tempo: " << mediaTempoArvoreB << endl;

            saida << "MÉDIA FINAL ARVORE B COM M = 200:" << endl;
            saida << "Numero de comparacoes : " << mediaComparacoesArvoreB2 << endl;
            saida << "Tempo: " << mediaTempoArvoreB2 << endl;

            saida.close();
}

void metricasMetodosCompressao()
{
     cout << "Inicializando contabilizacao de metricas dos metodos de compressao" << endl;
     int m = 3;

     ofstream saida(globalPath + "/saida.txt"); 
     for(int i = 0; i < m; i++)
     {
        int n = 100;

        ProductReview *reviews = new ProductReview[n];
        reviews = import(n);

        string cadeia;

        for(int j = 0; j < n; j++)
        {
            ProductReview review = reviews[j];
            cadeia += review.getUserId();
            cadeia += review.getProductId();
            cadeia += review.getTimestamp();
        }

        saida << "<<-------------------------- Executando " << i + 1 << " metrica -------------------------->>" << endl;
        saida << "Tamanho da cadeia original: " << cadeia.size() << endl;
        saida << "cadeia original : " << cadeia << endl;

        high_resolution_clock::time_point start = high_resolution_clock::now();
        Huffman* h = new Huffman();
        string comprimido = h->comprime(cadeia);
        codigo = h->getCodigo();
        high_resolution_clock::time_point end = high_resolution_clock::now();
        double tempoExec = duration_cast<duration<double>>(end - start).count();
        saida << "Tamanho da cadeia comprimida: " << comprimido.size() / 8 << endl;
        saida << "cadeia comprimida : " << comprimido << endl;
        saida << "Taxa de compressao:" << h->taxaCompressao(cadeia, comprimido) << " porcento" << endl;
        saida << "Tempo de execucao: " << tempoExec << endl;

     }

} 



int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "ERRO: Número de argumentos invalido! Passe a path do arquivo na execucao." << endl;
        return 0;
    }

    // atribui a path passada como argumento a variável path:
    string path = argv[1];
    globalPath = path;

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

    cout << "Escolha a etapa a ser executada: " << endl;
    cout << "1- Metricas dos algoritmos de ordenacao" << endl;
    cout << "2- Metricas das estruturas balanceadas" << endl;
    cout << "3- Metricas dos metodos de compressao" << endl;

    int opcao;
    cin >> opcao;

    switch(opcao)
    {
        case 1:
            metricasOrdenacao();
            break;
        case 2:
            metricasEstruturasBalanceadas();
            break;
        case 3:
            metricasMetodosCompressao();
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
    }
}
