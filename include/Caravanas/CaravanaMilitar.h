//
// Created by Pedro on 12/17/2024.
//

#ifndef SIMDESERTO_CARAVANAMILITAR_H
#define SIMDESERTO_CARAVANAMILITAR_H
#include "../Caravana.h"

class CaravanaMilitar : public Caravana {
public:
    CaravanaMilitar(int linha, int coluna); // Values: 40 Tripulantes, 400L Agua, 5T CargaMaxima

    void atualizarTurno();
};

#endif //SIMDESERTO_CARAVANAMILITAR_H
