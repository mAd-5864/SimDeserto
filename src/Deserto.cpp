//
// Created by Pedro on 11/3/2024.
//

#include "../include/Deserto.h"

// Construtor: inicializa o mapa com pontos (.)
Deserto::Deserto(int linhas, int colunas)
        : linhas(linhas), colunas(colunas), mapa(linhas * colunas, '.') {}

// Calcula o índice no vetor com base na linha e coluna
int Deserto::calcularIndice(int linha, int coluna) const {
    return (linha * colunas) + coluna;
}

void Deserto::setLinhas(int linhas) {
    this->linhas = linhas;
}

void Deserto::setColunas(int colunas) {
    this->colunas = colunas;
}

// Lê a config de um ficheiro
bool Deserto::lerFicheiro(const std::string &filename) {
    std::string folder = "../config/";
    std::string path = folder + filename;

    std::ifstream file(path);
    if (!file) {
        std::cerr << "Erro ao abrir o ficheiro: " << filename << std::endl;
        return false;
    }

    std::string lixo;
    int nLinhas, nColunas;

    // Ler as primeiras duas linhas com os tamanhos
    file >> lixo >> nLinhas;
    setLinhas(nLinhas);
    std::cout << "Linhas: " << nLinhas << std::endl;

    file >> lixo >> nColunas;
    setColunas(nColunas);
    std::cout << "Colunas: " << nColunas << std::endl;

    // Validar valores de linhas e colunas
    if (nLinhas <= 0 || nColunas <= 0) {
        std::cerr << "Erro: Configuração inválida para linhas ou colunas." << std::endl;
        return false;
    }


    mapa.resize(nLinhas * nColunas, ' ');
    // Ler cada linha do mapa
    std::string line;
    for (int i = 0; i <= nLinhas && std::getline(file, line); ++i) {
        for (int j = 0; j < std::min(nColunas, static_cast<int>(line.size())); ++j) {
            mapa[calcularIndice(i-1, j)] = line[j];
        }
    }
    mostrarMapa();
    return true;
}

// Mostra o mapa na consola
void Deserto::mostrarMapa() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << mapa[calcularIndice(i, j)] << ' ';
        }
        std::cout << '\n';
    }
}

char Deserto::getTerreno(int linha, int coluna) const {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        return mapa[calcularIndice(linha, coluna)];
    }
    return ' '; // Posição inválida
}

void Deserto::setTerreno(int linha, int coluna, char terreno) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        mapa[calcularIndice(linha, coluna)] = terreno;
    }
}

