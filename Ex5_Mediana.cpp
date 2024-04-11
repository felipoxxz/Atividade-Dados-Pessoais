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

void Merge(Pessoa arranjo[], int inicio, int meio, int fim, string campo) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Pessoa L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arranjo[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arranjo[meio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = inicio;

    while (i < n1 && j < n2) {
        if ((campo == "altura" && L[i].altura <= R[j].altura) || (campo == "peso" && L[i].peso <= R[j].peso)) {
            arranjo[k] = L[i];
            i++;
        } else {
            arranjo[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arranjo[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arranjo[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(Pessoa arranjo[], int inicio, int fim, string campo) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        MergeSort(arranjo, inicio, meio, campo);
        MergeSort(arranjo, meio + 1, fim, campo);
        Merge(arranjo, inicio, meio, fim, campo);
    }
}


float CalcularMediana(Pessoa arranjo[], int tamanho, string campo) {
    if (tamanho % 2 == 0) {
        if (campo == "altura") {
            return (arranjo[tamanho / 2 - 1].altura + arranjo[tamanho / 2].altura) / 2.0;
        } else if (campo == "peso") {
            return (arranjo[tamanho / 2 - 1].peso + arranjo[tamanho / 2].peso) / 2.0;
        }
    } else {
        if (campo == "altura") {
            return arranjo[tamanho / 2].altura;
        } else if (campo == "peso") {
            return arranjo[tamanho / 2].peso;
        }
    }
    return 0.0;
}

int main() {
    auto inicio = high_resolution_clock::now();

    int qtdElementos = Contagem("C:\\Users\\felipe\\Documents\\dados_pessoais.csv");
    Pessoa Arranjo[qtdElementos];
    Leitura_csv("C:\\Users\\felipe\\Documents\\dados_pessoais.csv", Arranjo);

    MergeSort(Arranjo, 0, qtdElementos - 1, "altura");
    float medianaAltura = CalcularMediana(Arranjo, qtdElementos, "altura");

    MergeSort(Arranjo, 0, qtdElementos - 1, "peso");
    float medianaPeso = CalcularMediana(Arranjo, qtdElementos, "peso");

    cout << "Mediana da altura: " << medianaAltura << " metros" << endl;
    cout << "Mediana do peso: " << medianaPeso << " kg" << endl;

    auto fim = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(fim - inicio);
    cout << "Tempo de execução: " << duration.count() << " milissegundos" << endl;

    return 0;
}