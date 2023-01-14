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

// falta tratar colisões e adicionar registros não repetidos:
void createTable(string &path, int registros)
{
    ProductReview *reviews = import(registros);
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

void printPrompt(ProductReview *vet, int n)
{
    char imp;
    cout << "Imprimir (s/n): ";
    cin >> imp;

    if(vet == NULL)
        cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
    else if(imp == 's')
    {
        for(int i = 0; i < n; i++)
            vet[i].print();
    }
}

void printPrompt(ArvoreVP *arv, int n)
{
    char imp;
    cout << "Imprimir (s/n): ";
    cin >> imp;

    if(arv == NULL)
        cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
    else if(imp == 's')
        arv->print();
}

void printPrompt(ArvoreB *arv, int n)
{
    char imp;
    cout << "Imprimir (s/n): ";
    cin >> imp;

    if(arv == NULL)
        cout << "ALERTA: ponteiro nulo, nada a imprimir!" << endl;
    else if(imp == 's')
        arv->print();
}

ProductReview* randomTest(int n)
{
    ProductReview *vet = new ProductReview[n];

    for(int i = 0; i < n; i++)
    {
        string u("STR");
        u += 'a'+rand()%('z'-'a');
        //vet[i].userId = u; // ou essa linha ou a de baixo pode ser usada, dependendo de como foi implementado (a de baixo é preferencial)
        vet[i].setUserId(u);
    }

    return vet;
}

template<typename T>
void treeTest(T arv, ProductReview *vet, int n)
{
    for(int i = 0; i < n; i++)
        arv->insere(&vet[i]);
    printPrompt(vet, n);

    string userId, productId;
    cout << "Digite um par (userId, productId) para busca: ";
    cin >> userId >> productId;
    while(userId != "quit")
    {
        ProductReview *p = arv->busca(userId, productId);
        if(p != NULL)
            p->print();
        else
            cout << "Produto nao encontrado!" << endl;
        
        cout << "Digite outro par (userId, productId) para busca: ";
        cin >> userId >> productId;
    }
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
    }else{
        return comprime;
    }
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

void compressTest(int method)
{
    ifstream input(globalPath + "/reviewsOrig.txt");

    
    switch(method)
    {
        case 0: cout << "=== Teste Huffman ===" << endl << endl; break;
        case 1: cout << "=== Teste LZ77 ===" << endl << endl; break;
        case 2: cout << "=== Teste LZW ===" << endl << endl; break;
        default: cout << "Metodo de compressao nao suportado" << endl << endl; break;
    }
    
    cout << "Testando strings..." << endl;

    string str = "abracadabra";

    string comp = comprime(str, method);

    string orig = descomprime(comp, method);

    cout << "String comprimida: " << comp << endl;
    cout << "String descomprimida: " << orig << endl << endl;
 
    cout << "Testando arquivos..." << endl;

    comprime(method); // essa função deve comprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsOrig.txt'
    descomprime(method); // essa função deve descomprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsComp.bin'
}







int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        // OBS.: TODOS OS ARQUIVOS USADOS NO PROGRAMA (TANTO DE ENTRADA QUANTO DE SAÍDA) DEVEM ESTAR LOCALIZADOS NO DIRETÓRIO FORNECIDO
        // PELO USUÁRIO COMO ARGUMENTO DA LINHA DE COMANDO
        std::string path(argv[1]);
        createBinary(path);

        int registerIdx;
        cout << "Digite um indice de registro (-1 para sair): ";
        cin >> registerIdx;
        while (registerIdx != -1)
        {
            getReview(registerIdx);
            cout << "Digite outro indice de registro (-1 para sair): ";
            cin >> registerIdx;
        }

        ProductReview *vet = 0;
        ArvoreVP *arv_vp = 0;
        ArvoreB *arv_b = 0;
        int option, n;
        do
        {
            cout << "[1] Vetor de teste" << endl 
                << "[2] Importar registros" << endl
                << "[3] Arvore vermelho-preto" << endl
                << "[4] Arvore B" << endl
                << "[5] Huffman" << endl
                << "[6] LZ77" << endl
                << "[7] LZW" << endl
                << "[0] Sair" << endl;

            cout << "Digite uma opcao de menu: ";
            cin >> option;
            switch (option)
            {
                case 1:
                    n = 10;
                    delete [] vet;
                    vet = randomTest(n);
                    printPrompt(vet, n);
                    break;
                case 2:
                    cout << "Quantos registros deseja importar? ";
                    cin >> n;
                    delete [] vet;
                    vet = import(n);
                    printPrompt(vet, n);
                    break;
                case 3:
                    delete arv_vp;
                    arv_vp = new ArvoreVP();
                    treeTest(arv_vp, vet, n);
                    break;
                case 4:
                    delete arv_b;
                    arv_b = new ArvoreB();
                    treeTest(arv_b, vet, n);
                    break;
                case 5:
                    compressTest(0);
                    break;
                default:
                    break;
            }
        } while(option != 0);

        delete [] vet;
        delete arv_vp;
        delete arv_b;
    }

    return 0;
}
