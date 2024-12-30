//
// Created by Pedro on 11/3/2024.
//

#include "../include/Caravana.h"

// Static ID generator
int Caravana::nextID;

// Constructor for base Caravana
Caravana::Caravana(int cargaMax, int aguaMax, int tripulantesMax, int tipoMov, int maxMoves, int linha, int coluna)
        : ID(nextID++), cargaMaxima(cargaMax), aguaMax(aguaMax), tripulantesMax(tripulantesMax),
          tipoMovimentacao(tipoMov), maxMoves(maxMoves), linha(linha), coluna(coluna) {
    // Os valores numTripulantes, qntAgua, e qntMerc já são inicializados implicitamente como 0
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

bool Caravana::mover(int novaLinha, int novaColuna) {
    posAnterior = std::make_pair(linha, coluna);
    if (movesRestantes>0){
        linha = novaLinha;
        coluna = novaColuna;
        movesRestantes--;
        return true;
    } else std::cout << "Ja atingiu maximo de movimentos neste turno\n";
    return false;
}

bool Caravana::estaNaCidade(const std::vector<Cidade>& cidades) const {
    for (const Cidade& cidade : cidades) {
        if (cidade.getLinha() == linha && cidade.getColuna() == coluna) {
            return true;
        }
    }
    return false;
}

bool Caravana::carregar(int quantidade) {
    if(qntMerc+quantidade <= cargaMaxima){
        qntMerc += quantidade;
        return true;
    }
    else{
        std::cerr << "Caravana "<<ID<< " so tem capacidade para mais " <<cargaMaxima-qntMerc <<"T de mercadoria\n";
     return false;
    }
}

bool Caravana::addTripulantes(int quantidade){
    if(numTripulantes+quantidade <= tripulantesMax){
        numTripulantes += quantidade;
        return true;
    }
    else{
        std::cerr << "Caravana "<<ID<< " so tem capacidade para mais " <<tripulantesMax-numTripulantes <<" tripulantes\n";
        return false;
    }
}