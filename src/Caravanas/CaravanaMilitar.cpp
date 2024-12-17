//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaMilitar.h"

// Constructor for CaravanaMilitar
CaravanaMilitar::CaravanaMilitar(int linha, int coluna)
        : Caravana(5, 1, linha, coluna) { // 5T carga, movimentacao tipo 1
    numTripulantes = 40;
    qntAgua = 400;
    qntMerc = 0;
}