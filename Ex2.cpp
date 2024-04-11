#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int Contagem(string nome)
{
    ifstream arquivo(nome);

    if (!arquivo.is_open())
        throw runtime_error("Arquivo não pôde ser lido");

    string linha;

    int quantidade = -1;
    
    while (getline(arquivo, linha))
    {
        quantidade++;
    }
    arquivo.close();
    return quantidade;
}

int main()
{
    int qtdElementos = Contagem("C:\\Users\\felipe\\Documents\\dados_pessoais.csv");

    cout << "O Número de elementos é: " << qtdElementos;
}
