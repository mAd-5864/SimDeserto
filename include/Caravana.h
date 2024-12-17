#ifndef SIMDESERTO_CARAVANA_H
#define SIMDESERTO_CARAVANA_H

#include "Utils.h"

class Caravana {
protected:
    int ID, numTripulantes, qntAgua, qntMerc;
    const int cargaMaxima;
    int tipoMovimentacao; // 0-Sem tripulantes, 1-Utilizador, 2-Autónomo
    int linha, coluna;

public:
    Caravana(int cargaMax, int tipoMov, int linha, int coluna);
    virtual ~Caravana();

    // Common methods (add getters, setters, or virtual methods here if needed)
};
#endif //SIMDESERTO_CARAVANA_H