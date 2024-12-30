//
// Created by Tiago on 26/12/2024.
//

#include "../include/Tempestade.h"


Tempestade::Tempestade(int linha, int coluna, int raio):linha(linha), coluna(coluna), raio(raio) {}

bool Tempestade::verificaDentro(int linhaCaravana, int colunaCaravana) const{
    if (linhaCaravana<=linha+raio && linhaCaravana>= linha-raio &&
        colunaCaravana<=coluna+raio && colunaCaravana>= coluna-raio)
        return true;

    return false;
}