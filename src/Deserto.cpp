//
// Created by Pedro on 11/3/2024.
//

#include "../include/Deserto.h"

// Construtor
// Inicializa a matriz com pontos (.) para representar o deserto vazio
Deserto::Deserto(int linha, int coluna) : linha(linha), coluna(coluna) {
    map.resize(linha, std::vector<char>(coluna, '.'));
}

// Destrutor da classe
Deserto::~Deserto() {
    // Limpeza, se necessário (por exemplo, desalocar memória dinâmica, se aplicada futuramente)
}

bool Deserto::loadMap(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro do mapa " << filename << std::endl;
        return false;
    }

    // Redimensiona o mapa e inicializa com o deserto vazio ('.')
    map.resize(linha, std::vector<char>(coluna, '.'));

    // Lê o mapa do ficheiro e armazena-o na matriz
    for (int i = 0; i < linha; ++i) {
        std::string line;
        if (std::getline(file, line)) {
            for (int j = 0; j < std::min(coluna, static_cast<int>(line.size())); ++j) {
                map[i][j] = line[j];
            }
        }
    }

    file.close();
    return true;
}

void Deserto::displayMap() const {
    for (const auto &row : map) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
}

char Deserto::getTerrain(int linha, int coluna) const {
    if (linha >= 0 && linha < this->linha && coluna >= 0 && coluna < this->coluna) {
        return map[linha][coluna];
    }
    return ' '; // Retorna espaço em branco se a posição é inválida
}

void Deserto::setTerrain(int linha, int coluna, char terreno) {
    if (linha >= 0 && linha < this->linha && coluna >= 0 && coluna < this->coluna) {
        map[linha][coluna] = terreno;
    }
}

