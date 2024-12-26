//
// Created by Pedro on 12/17/2024.
//
#ifndef SIMDESERTO_CARAVANASECRETA_H
#define SIMDESERTO_CARAVANASECRETA_H

#include "../Caravana.h"

class CaravanaSecreta : public Caravana {
    // Podia ser uma caravana infiltrada que seguia os barbaros sem ser detetada
    // Avisando os Militares para perseguir e os Mercadores para se afastarem
public:
    CaravanaSecreta(int linha, int coluna);

    void atualizarTurno();
    std::pair<int, int> autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros);
    std::pair<int, int> moveMorrer();
};

#endif //SIMDESERTO_CARAVANASECRETA_H

// a cada instantes chance de ser apanhada aumenta 2%
// se for apanhada é destruida
// a cada turno chance de 70% de matar 1 barbaro ou perder 1 espiao
// caso um barbaro morra chance de ser apanhada aumenta +2%
// se a caravana barbara desaparecer com os espioes infiltrados, ganha 50 moedas
