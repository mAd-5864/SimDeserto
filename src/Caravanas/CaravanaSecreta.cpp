//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaSecreta.h"

// Constructor for CaravanaSecreta
CaravanaSecreta::CaravanaSecreta(int linha, int coluna)
        : Caravana(5, 200, 10, 1, 4, linha, coluna) { // Exemplo: 5T cargaMaxima, 200 litrosMaximo, movimentacao tipo 1
    numTripulantes = tripulantesMax;
    qntAgua = aguaMax;
    qntMerc = 0;
    movesRestantes = maxMoves;
    tipo = 'S';
}

void CaravanaSecreta::atualizarTurno() {
    if (numTripulantes==0){
        // destruida
    }
    else qntAgua-=2;
    movesRestantes = maxMoves;
}