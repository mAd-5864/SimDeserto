//
// Created by Pedro on 11/3/2024.
//

#include "../include/Barbaro.h"

int Barbaro::nextID = 1;

// Construtor
Barbaro::Barbaro(int lin, int col, int maxTripulantes, int turnosRestantes) : ID(nextID++), linha(lin), coluna(col), turnosRestantes(turnosRestantes), maxTripulantes(maxTripulantes) {
    numTripulantes = maxTripulantes;
}

bool Barbaro::atualizar(){
    if (estaAborrecido() || numTripulantes == 0) return false;
    turnosRestantes--;
    return true;
}

// Movimenta o bárbaro aleatoriamente para uma posição adjacente
void Barbaro::move(int novaLinha, int novaColuna) {
    linha = novaLinha;
    coluna = novaColuna;

}

bool Barbaro::perseguirCaravana(int destinoLinha, int destinoColuna) {
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