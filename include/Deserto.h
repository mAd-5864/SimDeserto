//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_DESERTO_H
#define SIMDESERTO_DESERTO_H

#include "Utils.h"

class Deserto {
private:
    int linha, coluna;                      // Dimensões do mapa
    std::vector<std::vector<char>> map;     // Matriz bidimensional para o mapa

public:
    // Construtor
    Deserto(int linha, int coluna);
    ~Deserto();

    bool loadMap(const std::string &filename);
    void displayMap() const;
    char getTerrain(int linha, int coluna) const;

    // Define o tipo de terreno numa posição específica
    void setTerrain(int linha, int coluna, char terreno);

    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
};

#endif //SIMDESERTO_DESERTO_H
