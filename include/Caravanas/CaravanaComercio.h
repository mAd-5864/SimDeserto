//
// Created by Pedro on 12/17/2024.
//
#ifndef SIMDESERTO_CARAVANACOMERCIO_H
#define SIMDESERTO_CARAVANACOMERCIO_H

#include "../Caravana.h"

class CaravanaComercio : public Caravana {
public:
    // Constructor
    CaravanaComercio(int linha, int coluna);

    bool ataqueTempestade(int probabilidade);
    void atualizarTurno();
    std::pair<int, int> autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros);
    std::pair<int, int> moveMorrer();
};

#endif //SIMDESERTO_CARAVANACOMERCIO_H