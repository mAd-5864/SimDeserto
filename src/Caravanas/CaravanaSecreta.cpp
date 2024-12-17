//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaSecreta.h"

// Constructor for CaravanaSecreta
CaravanaSecreta::CaravanaSecreta(int linha, int coluna)
        : Caravana(10, 1, linha, coluna) { // Exemplo: 10T carga, movimentacao tipo 1
    numTripulantes = 10;
    qntAgua = 100;
    qntMerc = 0;
}