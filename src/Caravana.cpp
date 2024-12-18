//
// Created by Pedro on 11/3/2024.
//

#include "../include/Caravana.h"

// Constructor for base Caravana
Caravana::Caravana(int cargaMax, int aguaMax, int tipoMov, int linha, int coluna)
        : cargaMaxima(cargaMax), aguaMax(aguaMax), tipoMovimentacao(tipoMov),
          linha(linha), coluna(coluna),
          numTripulantes(0), qntAgua(0), qntMerc(0) {}

// Destructor
Caravana::~Caravana() {
    // Any cleanup if necessary
}

std::string converterTipoCaravana(char tipo) {
    switch (tipo) {
        case 'C': return "Mercadoria";
        case 'M': return "Militar";
        case 'S': return "Secreta";
        default: return ""; // Tipos inválidos
    }
}