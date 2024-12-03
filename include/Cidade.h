//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_CIDADE_H
#define SIMDESERTO_CIDADE_H

#include "Utils.h"

class Cidade {
private:
    char nome;  // Nome da cidade
    std::map<std::string, bool> caravanasDisponiveis;  // Tipo de caravana e disponibilidade

public:
    // Construtor
    explicit Cidade(char nome);

    // Mostra caravanas disponíveis
    void mostrarCaravanasDisponiveis() const;

    // Compra uma caravana
    bool comprarCaravana(char tipo);

};


#endif //SIMDESERTO_CIDADE_H
