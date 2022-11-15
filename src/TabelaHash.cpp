#include "../headers/RegistroHash.h"
#include "../headers/TabelaHash.h"
#include "../headers/sorts.h"

#include <iostream>
#include <fstream>

#include <list>

using namespace std;

// cria tabela hash:
TabelaHash::TabelaHash(int n)
{
    this->total = n;
    this->cont = 0;
    this->colisoes = 0;

    // define o tamanho da tabela:
    this->primo = criaPrimo(n);
    cout << "Primo: " << primo << endl;

    // cria a tabela com tamanho primo:
    this->table = createTable(primo);
}

// desaloca a memória da tabela:
TabelaHash::~TabelaHash()
{
    // desaloca a memória da tabela:
    delete[] this->table;
}

// cria a tabela com tamanho primo:
list<RegistroHash> *TabelaHash::createTable(int n)
{
    // declara lista de registros hash para a tabela:
    list<RegistroHash> *table = new list<RegistroHash>[n];

    // retorna a tabela criada:
    return table;
}

// cria função hash:
int TabelaHash::hashPolinomial(string &s, int &n)
{

    // inicializa variáveis constantes para a função hash:
    const int p = 53, m = 1e9 + 9;
    // inicializa variáveis auxiliares para a função hash:
    int hash = 0;
    long long p_pow = 1;

    // percorre a string e atualiza variáveis auxiliares:
    for (int i = 0; i < s.length(); i++)
    {
        hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    // retorna o valor da função hash:
    return abs(hash) % n;
}

// define o tamanho da tabela hash como o número primo mais próximo:
int TabelaHash::criaPrimo(int n)
{

    // define variáveis auxiliares:
    int i, j;
    bool flag = false;

    // atualiza n para o próximo número primo:
    while (!flag)
    {
        for (i = 2; i < n / 2; i++)
        {
            if (n % i == 0)
            {
                flag = false;
                n++;
            }
            else
            {
                flag = true;
            }
        }
    }

    // retorna o número primo:
    return n;
}

// insere um item na tabela hash:
void TabelaHash::inserirItem(string value)
{
    // calcula o índice de inserção:
    int index = hashPolinomial(value, total);
    // //atualiza o contador de registros na posição:

    // calcula índice da chave na tabela:
    if (this->table[index].size() > 0)
    {
        for (auto it = this->table[index].begin(); it != this->table[index].end(); it++)
        {
            if (it->productId == value)
            {
                // atualiza o contador de registro:
                it->qtdReviews++;
                return;
            }
        }
        // atuazliza o contador de colisões:
        this->colisoes++;
    }
    this->cont++;

    // insere registro hash na tabela:
    RegistroHash novoRegistro = {value, 1};
    this->table[index].push_back(novoRegistro);
}

// imprime a tabela hash:
void TabelaHash::printTable()
{

    // percorre a tabela:
    for (int i = 0; i < primo; i++)
    {
        cout << "Index " << i << ": ";
        // impime os registros:
        for (RegistroHash j : table[i])
            cout << "productId: " << j.productId << " qtdReviews: " << j.qtdReviews << " => ";
        cout << endl;
    }

    // imprime o número de colisões:
    cout << "Total de colisoes: " << this->colisoes << endl;
}

RegistroHash *TabelaHash::createVetor()
{
    RegistroHash *vetor = new RegistroHash[this->cont];
    int j = 0;
    for (int i = 0; i < primo; i++)
    {
        if (table[i].size() > 0)
        {
            for (RegistroHash k : table[i])
            {
                vetor[j] = k;
                j++;
            }
        }
    }
    return vetor;
}

void TabelaHash::ordenaTabela(int p)
{
    RegistroHash *vetor = createVetor();

    // ordena o vetor:
    cout << "Ordenando tabela..." << endl;
    quickSortDecrescente(vetor, 0, this->cont - 1);

    for (int i = 0; i < p; i++)
    {
        cout << "productId: " << vetor[i].productId << " qtdReviews: " << vetor[i].qtdReviews << endl;
    }

    // libera a memória do vetor:
    delete[] vetor;
}