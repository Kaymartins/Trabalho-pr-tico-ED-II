#include <iostream>
#include <fstream>

using namespace std;


void createBinary(string& path)
{
    //cria arquivo binário:
    FILE *arq;

    arq = fopen(path.c_str(),);
    fstream arq(path,ios::out | ios::binary);
    int vet[100];
    int resultado;
    while (!arq.eof())
    {
        new ProductReview  = fread(&vet[0], sizeof(int), 100, arq);
    }
    //lê o arquivo até o fim e escreve no arquivo binário:
    while(!arq.eof())
    {
        
    }

    arq.close();
}

int main()
{
    cout<<"Hello World";

    return 0;
}


