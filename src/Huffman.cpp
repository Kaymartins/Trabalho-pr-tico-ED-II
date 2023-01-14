#include "../headers/Huffman.h"
#include "../headers/Fila.h"


void Huffman::huffman(string str)
{
    //cria um vetor de frequencia com a quantidade total de caracteres possíveis inicializando todos com zero.
    unordered_map<char, int> freq;
    for(char c: str)
        freq[c]++;

    int tam = freq.size();
    int *frequencia = new int[tam];
    char *caracteres = new char[tam];

    for(int i = 0; i < tam; i++)
    {
        caracteres[i] = freq.begin()->first;
        frequencia[i] = freq.begin()->second;
        freq.erase(freq.begin());
    }



    //cria uma fila de prioridade para armazenar os nós da árvore de huffman
    Queue *pq = new Queue();

    for(int i = 0; i < tam; i++)
    {
        //se o caractere apareceu pelo menos uma vez, cria um nó para ele e adiciona na fila de prioridade
        pq->enqueue(HuffmanNo(caracteres[i], frequencia[i]));
    }
    
    //construindo a arvore de huffman
    HuffmanNo *esq, *dir, *top;

    while(pq->getSize() != 1){
        //pega os dois nós com mais frequencia da fila de prioridadade, insere na arvore e remove da fila
        esq = new HuffmanNo(pq->getFront()); pq->dequeue();
        dir = new HuffmanNo(pq->getFront()); pq->dequeue();
        //realiza a soma entre eles e cria um novo nó com a soma das frequencias sendo pai dos dois nós anteriores
        int soma = esq->freq + dir->freq;
        top = new HuffmanNo('\0', soma);
        top->esq = esq;
        top->dir = dir;
        pq->enqueue(*top);
    }

    raiz = new HuffmanNo(pq->getFront());
    //armazena o código de huffman para cada caractere
    codigoHuffman(raiz, "");

    //imprime o código de huffman para cada caractere
    print(raiz, "");

}


void Huffman::codigoHuffman(HuffmanNo* raiz, string str)
{
    if(!raiz)
        return;
    if(raiz->c != '\0')
        codigo[raiz->c] = str;

    codigoHuffman(raiz->esq, str + "0");
    codigoHuffman(raiz->dir, str + "1");
}

string Huffman::comprime(string s)
{
    huffman(s);
    string stringComprimida = "";
    for(char c: s)
        stringComprimida += codigo[c];
    return stringComprimida;
}

void Huffman::print(HuffmanNo* raiz, string str)
{
    if(!raiz)
        return;
    if(raiz->c != '\0')
        cout << raiz->c << ": " << str << endl;
    print(raiz->esq, str + "0");
    print(raiz->dir, str + "1");
}

string Huffman::descomprime(string str, unordered_map<char, string> cod)
{
    string descomprimido = "";
    string atual = "";

    for (char c: str)
    {
        atual += c;
        for (auto i: cod)
        {
            if (i.second == atual)
            {
                descomprimido += i.first;
                atual = "";
            }
        }
    }
    return descomprimido;
}

unordered_map<char, string> Huffman::getCodigo()
{
    return codigo;
}