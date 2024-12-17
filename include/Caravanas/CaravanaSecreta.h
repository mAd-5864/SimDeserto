//
// Created by Pedro on 12/17/2024.
//
#ifndef SIMDESERTO_CARAVANASECRETA_H
#define SIMDESERTO_CARAVANASECRETA_H

#include "../Caravana.h"

class CaravanaSecreta : public Caravana {
    // Podia ser uma caravana espiao que seguia os barbaros sem ser detetada
    // Avisando os Militares para perseguir e os Mercadores para se afastarem
public:
    CaravanaSecreta(int linha, int coluna);
};

#endif //SIMDESERTO_CARAVANASECRETA_H

