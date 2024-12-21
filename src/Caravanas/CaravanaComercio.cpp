//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaComercio.h"

// Constructor
CaravanaComercio::CaravanaComercio(int linha, int coluna)
        : Caravana(40, 200, 20, 1, 2, linha, coluna) { // 40T cargaMaxima, 200 litrosMaximo, movimentacao tipo 1
    numTripulantes = tripulantesMax;
    qntAgua = aguaMax;
    qntMerc = 0;
    movesRestantes = maxMoves;
    tipo = 'C';
}

void CaravanaComercio::atualizarTurno() {
    if (numTripulantes==0){
        // mover aleatoriamente
        // passados 5 instantes, acaba por desaparecer
    }
    else if (numTripulantes<tripulantesMax/2) qntAgua--;
    else qntAgua-=2;
    movesRestantes = maxMoves;
}

