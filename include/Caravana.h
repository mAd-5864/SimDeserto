//
// Created by Pedro on 11/3/2024.
//

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
    ~Caravana();
};

class CaravanaComercio: public Caravana{
protected:

public:
    CaravanaComercio(Position posicaoInicial); // Valores Iniciais: 20 Tripulantes, 200L Agua, 40T CargaMaxima, movimentacao-1

};

class CaravanaMilitar: public Caravana{
protected:

public:
    CaravanaMilitar(Position posicaoInicial); // Valores Iniciais: 40 Tripulantes, 400L Agua, 5T CargaMaxima, movimentacao-1

};

class CaravanaSecreta: public Caravana{
    // Podia ser uma caravana espiao que seguia os barbaros sem ser detetada
    // Avisando os Militares para perseguir e os Mercadores para se afastarem
protected:

public:
    CaravanaSecreta(Position posicaoInicial);

};

class CaravanaBarbara: public Caravana{
protected:
    const int tipoMovimentacao = 2; // Se calhar deve ser no construtor
    int tempoRestante;
public:
    CaravanaBarbara(Position posicaoInicial); // Valores Iniciais: 40 Tripulantes, movimentacao-2

};
#endif //SIMDESERTO_CARAVANA_H
