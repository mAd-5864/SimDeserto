//
// Created by Tiago on 26/12/2024.
//

#include "../include/Tempestade.h"

Tempestade::Tempestade(int linha, int coluna, int raio):linha(linha), coluna(coluna), raio(raio) {}

int Tempestade::verificaDentro(int linha, int coluna) {
    if(this->linha >= linha && this->linha + this->raio <= linha
    && this->coluna >= coluna && this->coluna + this->raio <= coluna)
        return 0;
    else
        return 1;
}