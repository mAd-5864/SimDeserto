//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaComercio.h"

// Constructor
CaravanaComercio::CaravanaComercio(int linha, int coluna)
        : Caravana(40, 200, 20, 1, linha, coluna) { // 40T cargaMaxima, 200 litrosMaximo, movimentacao tipo 1
    qntAgua = aguaMax;
    qntMerc = 0;
    numTripulantes = tripulantesMax;
    tipo = 'C';
}
