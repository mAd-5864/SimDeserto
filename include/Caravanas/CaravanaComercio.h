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

    void atualizarTurno();
    std::pair<int, int> autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros);
};

#endif //SIMDESERTO_CARAVANACOMERCIO_H