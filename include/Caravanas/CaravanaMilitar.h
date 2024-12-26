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
    std::pair<int, int> autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros);
    std::pair<int, int> moveMorrer();
};

#endif //SIMDESERTO_CARAVANAMILITAR_H
