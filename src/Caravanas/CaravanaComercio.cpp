//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaComercio.h"

// Constructor
CaravanaComercio::CaravanaComercio(int linha, int coluna)
        : Caravana(40, 200, 20, 0, 2, linha, coluna) { // 40T cargaMaxima, 200 litrosMaximo, movimentacao tipo 1
    numTripulantes = tripulantesMax;
    qntAgua = aguaMax;
    qntMerc = 0;
    movesRestantes = maxMoves;
    instantesRestantes = 5;
    tipo = 'C';
}

void CaravanaComercio::atualizarTurno() {
    if (numTripulantes == 0) {
        tipoMovimentacao = 2;
        // mover aleatoriamente

    } else {
        instantesRestantes = 5;
        if (numTripulantes < tripulantesMax / 2) qntAgua--;
        else qntAgua -= 2;
        if (qntAgua < 0) {
            numTripulantes--;
            qntAgua = 0;
        }
    }
    movesRestantes = maxMoves;
}

std::pair<int, int>CaravanaComercio::autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros) {
    // Procurar caravanas a 4 posições de distancia
    int alidado = 0, linhaAliado, colunaAliado;
    int distanciaMin = 999, distancia;
    for (const auto &caravana: caravanas) {
        if (caravana->getId() != ID) {

            distancia = abs(caravana->getLinha() - linha) +
                        abs(caravana->getColuna() - coluna);

            if (distancia <= 4) {
                if (distancia < distanciaMin) {
                    distanciaMin = distancia;
                    alidado = caravana->getId();
                    linhaAliado = caravana->getLinha();
                    colunaAliado = caravana->getColuna();
                }
            }
        }
    }
    // Se encontrar um caravana próxima, persegue-o
    if (alidado) {
        int novaLinha = linha + (rand() % 3 - 1);
        int novaColuna = coluna + (rand() % 3 - 1);
        distancia = abs(linhaAliado - novaLinha);
                + abs(colunaAliado - novaColuna);

        while (distancia>4) {
         novaLinha = linha + (rand() % 3 - 1);
         novaColuna = coluna + (rand() % 3 - 1);
            distancia = abs(linhaAliado - novaLinha);
                    + abs(colunaAliado - novaColuna);
        }
        //std::cout<<ID<<" manteve-se perto da caravana "<<alidado<<"\n";

        return std::make_pair(novaLinha, novaColuna);
    }
    int novaLinha = linha + (rand() % 3 - 1);
    int novaColuna = coluna + (rand() % 3 - 1);
    return std::make_pair(novaLinha, novaColuna);
}

std::pair<int, int> CaravanaComercio::moveMorrer(){
    if (numTripulantes>0) tipoMovimentacao = 0;
    --instantesRestantes;
    return std::make_pair(linha+(rand() % 3 - 1), coluna+(rand() % 3 - 1));
}

int CaravanaComercio::ataqueTempestade(int probabilidade) {
    if( ( getCarga() * 100 / getMaxCarga() ) > 50 ){
        if (probabilidade <= 50){
            return 1;
        }
    }else{
        if (probabilidade < 25){
            return 1;
        }
    }
    retiraCarga(25);
    return 0;
}