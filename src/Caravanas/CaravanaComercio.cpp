//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaComercio.h"

// Constructor for CaravanaComercio
CaravanaComercio::CaravanaComercio(int linha, int coluna)
        : Caravana(40, 200, 1, linha, coluna) { // 40T cargaMaxima, 200 litrosMaximo, movimentacao tipo 1
    numTripulantes = 20;
    qntAgua = 200;
    qntMerc = 0;
    tipo = 'c';
}
