//
// Created by Pedro on 11/3/2024.
//

#include "../include/Barbaro.h"

// Construtor
Barbaro::Barbaro(int lin, int col) : linha(lin), coluna(col), turnosRestantes(60), maxTripulantes(40) {
    numTripulantes = maxTripulantes;
}

// Movimenta o bárbaro aleatoriamente para uma posição adjacente
void Barbaro::move(int novaLinha, int novaColuna) {
    linha = novaLinha;
    coluna = novaColuna;

    --turnosRestantes;
}

bool Barbaro::perseguirCaravana(int destinoLinha, int destinoColuna) {
    --turnosRestantes;
    int distancia = abs(linha - destinoLinha) +
                abs(coluna - destinoColuna);
    if (distancia > 1) {
        // Determinar direção para a linha
        if (linha < destinoLinha) {
            linha++;
        } else if (linha > destinoLinha) {
            linha--;
        }
    }

    distancia = abs(linha - destinoLinha) +
                    abs(coluna - destinoColuna);

    // Determinar direção para a coluna
    if (distancia > 1) {

        if (coluna < destinoColuna) {
            coluna++;
        } else if (coluna > destinoColuna) {
            coluna--;
        }
        distancia = abs(linha - destinoLinha) +
                    abs(coluna - destinoColuna);
    }
    if (distancia<=1) {
        return true; // Entra em combate!!
    }

    return false;
}