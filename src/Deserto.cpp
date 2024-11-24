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

// Lê o mapa de um ficheiro
bool Deserto::carregarMapa(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erro ao abrir o ficheiro: " << filename << std::endl;
        return false;
    }
    int nLinhas, nColunas;
    file >> nLinhas;
    setLinhas(nLinhas);
    file >> nColunas;
    setColunas(nColunas);


    for (int i = 0; i < linhas && !file.eof(); ++i) {
        std::string line;
        std::getline(file, line);

        for (int j = 0; j < std::min(colunas, static_cast<int>(line.size())); ++j) {
            mapa[calcularIndice(i, j)] = line[j];
        }
    }
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

