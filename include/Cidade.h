//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_CIDADE_H
#define SIMDESERTO_CIDADE_H

#include <iostream>
#include <map>

class Cidade {
private:
    char nome;  // Nome da cidade
    std::map<char, bool> caravanasDisponiveis;  // Tipo de caravana e disponibilidade
    int linha, coluna;

public:
    // Construtor
    Cidade(char nome, int l, int c);

    char getNome() const { return nome; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    // Mostra caravanas disponíveis
    void mostrarCaravanasDisponiveis() const; // CORRIGIR: mostrar caravanas estacionadas

    // Compra uma caravana
    bool comprarCaravana(char tipo);

};


#endif //SIMDESERTO_CIDADE_H
