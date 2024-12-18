//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaMilitar.h"

// Constructor for CaravanaMilitar
CaravanaMilitar::CaravanaMilitar(int linha, int coluna)
        : Caravana(5, 400, 40, 1, linha, coluna) { // 5T cargaMaxima, 400 litrosMaximo ,movimentacao tipo 1
    numTripulantes = tripulantesMax;
    qntAgua = aguaMax;
    qntMerc = 0;
    tipo = 'M';
}