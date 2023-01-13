#include "../headers/Huffman.h"

HuffmanNo* Huffman::getNo(char c, int freq, HuffmanNo* esq, HuffmanNo* dir){
        HuffmanNo* no = new HuffmanNo();
        no->c = c;
        no->freq = freq;
        no->esq = esq;
        no->dir = dir;
        return no;
}

void Huffman::huffman(string str)
{
    //cria um vetor de frequencia com a quantidade total de caracteres possíveis inicializando todos com zero.
    int freq[256] = {0};
    for (char c : str)
        freq[c]++;

    //cria uma fila de prioridade para armazenar os nós da árvore de huffman
    priority_queue<HuffmanNo*, vector<HuffmanNo*>, comparaNos> pq;
    for(int i = 0; i < 256; i++)
    {
        //se o caractere apareceu pelo menos uma vez, cria um nó para ele e adiciona na fila de prioridade
        if(freq[i] > 0){
            pq.push(getNo((char)i, freq[i], NULL, NULL));
        }
    }
    
    //construindo a arvore de huffman
    while(pq.size() != 1){
        //pega os dois nós com mais frequencia da fila de prioridadade, insere na arvore e remove da fila
        HuffmanNo *esq = pq.top(); pq.pop();
        HuffmanNo *dir = pq.top(); pq.pop();
        //realiza a soma entre eles e cria um novo nó com a soma das frequencias sendo pai dos dois nós anteriores
        int soma = esq->freq + dir->freq;
        pq.push(getNo('\0', soma, esq, dir));
    }

    //armazena o código de huffman para cada caractere
    codigoHuffman(pq.top(), "", codigo);

    raiz = pq.top();

    for(int i = 0; i < 256; i++)
    {
        if(codigo[i] != "")
            cout << (char)i << " " << codigo[i] << endl;
    }

}

void Huffman::codigoHuffman(HuffmanNo* raiz, string str, string codigo[])
{
    if(!raiz)
        return;
    if(raiz->c != '\0')
        codigo[raiz->c] = str;

    codigoHuffman(raiz->esq, str + "0", codigo);
    codigoHuffman(raiz->dir, str + "1", codigo);
}

string Huffman::comprime(string s)
{
    huffman(s);
    string stringComprimida = "";
    for(char c: s)
        stringComprimida += codigo[c];
    return stringComprimida;
}


