//
// Created by Pedro on 11/3/2024.
//

#include "../include/Caravana.h"

// Constructor for base Caravana
Caravana::Caravana(int cargaMax, int tipoMov, int linha, int coluna)
        : cargaMaxima(cargaMax), tipoMovimentacao(tipoMov),
          linha(linha), coluna(coluna),
          numTripulantes(0), qntAgua(0), qntMerc(0) {}

// Destructor
Caravana::~Caravana() {
    // Any cleanup if necessary
}
