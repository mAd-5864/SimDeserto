//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaComercio.h"

// Constructor
CaravanaComercio::CaravanaComercio(int linha, int coluna)
        : Caravana(40, 200, 20, 0, 2, linha, coluna) { // 40T cargaMaxima, 200 litrosMaximo, movimentacao tipo 1
    numTripulantes = tripulantesMax;
    qntAgua = aguaMax;
    qntMerc = 0;
    movesRestantes = maxMoves;
    instantesRestantes = 5;
    tipo = 'C';
}

void CaravanaComercio::atualizarTurno() {
    if (numTripulantes == 0) {
        // mover aleatoriamente
        if (instantesRestantes-- == 0);// passados 5 instantes, acaba por desaparecer
    } else {
            if (numTripulantes < tripulantesMax / 2) qntAgua--;
            else qntAgua -= 2;
        if (qntAgua < 0) {
            numTripulantes--;
            qntAgua = 0;
        }
    }
    movesRestantes = maxMoves;
}

std::pair<int, int> CaravanaComercio::autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros){}