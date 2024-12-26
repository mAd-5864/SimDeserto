//
// Created by Tiago on 26/12/2024.
//

#include <valarray>
#include "../include/Tempestade.h"


Tempestade::Tempestade(int linha, int coluna, int raio):linha(linha), coluna(coluna), raio(raio) {}

int Tempestade::verificaDentro(int linhaCaravana, int colunaCaravana) {
    int distancia = abs(linha - linhaCaravana)
    + abs(coluna - colunaCaravana);

    if (distancia <= raio){
        return 0;
    }

    return 1;
}