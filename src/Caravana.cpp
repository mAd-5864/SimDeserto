//
// Created by Pedro on 11/3/2024.
//

#include "../include/Caravana.h"

// Static ID generator
int Caravana::nextID = 1;

// Constructor for base Caravana
Caravana::Caravana(int cargaMax, int aguaMax, int tripulantesMax, int tipoMov, int linha, int coluna)
        : ID(nextID++), cargaMaxima(cargaMax), aguaMax(aguaMax), tripulantesMax(tripulantesMax),
          tipoMovimentacao(tipoMov), linha(linha), coluna(coluna) {
    // Os valores numTripulantes, qntAgua, e qntMerc já são inicializados implicitamente como 0
}

// Destructor
Caravana::~Caravana() {
    // Any cleanup if necessary
}

std::string converterTipoCaravana(char tipo) {
    switch (toupper(tipo)) {
        case 'C': return "de Comercio";
        case 'M': return "Militar";
        case 'S': return "Secreta";
        default: return ""; // Tipos inválidos
    }
}

void Caravana::detalhes() const{
    std::cout << "\tID: " << ID
              << " | Caravana " << converterTipoCaravana(tipo)
              << " | Posicao(" << linha << ", " <<coluna << ")\n\t"<<
              numTripulantes<<" Tripulantes | "<<qntAgua<< "L Agua | "<<qntMerc<< "T Mercadoria"<< std::endl;
}

