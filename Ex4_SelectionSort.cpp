#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>   // pair
#include <stdexcept> // runtime_error
#include <sstream>
#include <map>
#include <chrono>    // para medição de tempo

using namespace std;
using namespace std::chrono;

class Pessoa
{
public:
    string nome;
    string idade;
    float peso;
    float altura;
};

bool try_parse_int(const std::string &str, int &result)
{
    std::istringstream iss(str);
    return (iss >> result) && iss.eof();
}

int Contagem(string nome)
{
    // Create an input filestream
    ifstream arquivo(nome);

    // Make sure the file is open
    if (!arquivo.is_open())
        throw runtime_error("Arquivo não pôde ser lido");

    string linha;

    int quantidade = -1;
    // Read data, line by line
    while (getline(arquivo, linha))
    {
        quantidade++;
    }
    arquivo.close();
    return quantidade;
}

void Leitura_csv(string nome, Pessoa arranjo[])
{

    // Create an input filestream
    ifstream arquivo(nome);

    // Make sure the file is open
    if (!arquivo.is_open())
        throw runtime_error("O arquivo não pôde ser lido");

    // Helper vars
    string linha, coluna, valor;

    // Mapeando as Colunas
    map<int, string> colunas;
    int colIndex = 1;
    if (arquivo.good())
    {
        // Extract the first line in the file
        getline(arquivo, linha);
        // Create a stringstream from line
        stringstream ss(linha);

        // Extract each column name
        while (getline(ss, coluna, ';'))
        {
            colunas[colIndex] = coluna;
            colIndex++;
        }
    }
    // Read data, line by line
    int arrIndex = 0;
    while (getline(arquivo, linha))
    {
        // Create a stringstream of the current line
        colIndex = 1;
        stringstream ss(linha);
        Pessoa pessoa;
        while (getline(ss, linha, ';'))
        {
            if (colunas[colIndex] == "Nome")
                pessoa.nome = linha;
            else if (colunas[colIndex] == "Idade")
                pessoa.idade = linha;
            else if (colunas[colIndex] == "Peso (kg)")
                pessoa.peso = stof(linha);
            else if (colunas[colIndex] == "Altura (m)")
                pessoa.altura = stof(linha);
            colIndex++;
        }
        arranjo[arrIndex] = pessoa;
        arrIndex++;
    }

    arquivo.close();
}

void SelectionSort(Pessoa arranjo[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (arranjo[j].altura < arranjo[indiceMenor].altura) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            swap(arranjo[i], arranjo[indiceMenor]);
        }
    }
}

int main() {
    auto inicio = high_resolution_clock::now();

    int qtdElementos = Contagem("C:\\Users\\felipe\\Documents\\dados_pessoais.csv");
    Pessoa Arranjo[qtdElementos];
    Leitura_csv("C:\\Users\\felipe\\Documents\\dados_pessoais.csv", Arranjo);

    SelectionSort(Arranjo, qtdElementos);

    for (int i = 0; i < qtdElementos; i++) {
        cout << "Elemento " << i + 1 << ":" << endl;
        cout << "Nome: " << Arranjo[i].nome << endl;
        cout << "Idade: " << Arranjo[i].idade << endl;
        cout << "Peso: " << Arranjo[i].peso << endl;
        cout << "Altura: " << Arranjo[i].altura << endl;
        cout << endl;
    }

    auto fim = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(fim - inicio);
    cout << "Tempo de execução: " << duration.count() << " milissegundos" << endl;

    return 0;
}