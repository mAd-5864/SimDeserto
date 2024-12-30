//
// Created by Tiago on 26/12/2024.
//

#ifndef SIMDESERTO_TEMPESTADE_H
#define SIMDESERTO_TEMPESTADE_H


class Tempestade {
    int linha, coluna, raio;

public:
    Tempestade(int linha, int coluna, int raio);
    bool verificaDentro(int linha, int coluna) const;
};


#endif //SIMDESERTO_TEMPESTADE_H
