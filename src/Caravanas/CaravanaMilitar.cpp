//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaMilitar.h"

// Constructor for CaravanaMilitar
CaravanaMilitar::CaravanaMilitar(int linha, int coluna)
        : Caravana(5, 400, 40, 0, 3, linha, coluna) { // 5T cargaMaxima, 400 litrosMaximo ,movimentacao tipo 1
    numTripulantes = tripulantesMax;
    qntAgua = aguaMax;
    qntMerc = 0;
    movesRestantes = maxMoves;
    tipo = 'M';
}

void CaravanaMilitar::atualizarTurno() {
    if (numTripulantes == 0) {
        // desloca-se sempre na mesma direção do último movimento que fez
        // passados 7 instantes, acaba por desaparecer
        qntAgua--;
    } else {
        if (numTripulantes < tripulantesMax / 2) qntAgua--;
        else qntAgua -= 3;
        if (qntAgua < 0) {
            numTripulantes--;
            qntAgua = 0;
        }
    }
    if (qntAgua<0) qntAgua=0;
    movesRestantes = maxMoves;
}

std::pair<int, int> CaravanaMilitar::autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros){
    // Procurar barbaros a 6 posições de distancia
    int alvo = 0, linhaBarbaro, colunaBarbaro;
    int distanciaMin = 999, distancia;
    for (const auto &barbaro : barbaros) {
        distancia = abs(barbaro.getLinha() - linha) +
                    abs(barbaro.getColuna() - coluna);

        if (distancia<=6) {
            if (distancia < distanciaMin) {
                distanciaMin = distancia;
                alvo = barbaro.getId();
                linhaBarbaro = barbaro.getLinha();
                colunaBarbaro = barbaro.getColuna();
            }
        }
    }
    // Se encontrar um barbaro próxima, persegue-o
    if (alvo) {
        int novaLinha = linha;
        int novaColuna = coluna;
        int distanciaLinha = abs(linhaBarbaro-linha);
        int distanciaColuna = abs(colunaBarbaro-coluna);
        // Determinar direção para a coluna
        if (distanciaColuna > 1) {
            if (novaColuna < colunaBarbaro) {
                novaColuna++;
            } else if (novaColuna > colunaBarbaro) {
                novaColuna--;
            }
        }
        if (distanciaLinha>1){
            if (novaLinha < linhaBarbaro) {
                novaLinha++;
            } else if (novaLinha > linhaBarbaro) {
                novaLinha--;
            }
        }
        return std::make_pair(novaLinha, novaColuna);
    }
    return std::make_pair(linha, coluna);
}