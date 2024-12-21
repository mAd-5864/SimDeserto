//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaMilitar.h"

// Constructor for CaravanaMilitar
CaravanaMilitar::CaravanaMilitar(int linha, int coluna)
        : Caravana(5, 400, 40, 1, 3, linha, coluna) { // 5T cargaMaxima, 400 litrosMaximo ,movimentacao tipo 1
    numTripulantes = tripulantesMax;
    qntAgua = aguaMax;
    qntMerc = 0;
    movesRestantes = maxMoves;
    tipo = 'M';
}

void CaravanaMilitar::atualizarTurno() {
    if (numTripulantes==0){
        // desloca-se sempre na mesma direção do último movimento que fez
        // passados 7 instantes, acaba por desaparecer
    }
    else if (numTripulantes<tripulantesMax/2) qntAgua--;
    else qntAgua-=2;
    movesRestantes = maxMoves;
}