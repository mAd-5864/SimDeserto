//
// Created by Pedro on 12/17/2024.
//
#include "../../include/Caravanas/CaravanaSecreta.h"

// Constructor for CaravanaSecreta
CaravanaSecreta::CaravanaSecreta(int linha, int coluna)
        : Caravana(5, 200, 10, 0, 4, linha, coluna) { // Exemplo: 5T cargaMaxima, 200 litrosMaximo, movimentacao tipo 1
    numTripulantes = tripulantesMax;
    qntAgua = aguaMax;
    qntMerc = 0;
    movesRestantes = maxMoves;
    tipo = 'S';
}

void CaravanaSecreta::atualizarTurno() {
    if (numTripulantes == 0) {
        // destruida
    } else qntAgua -= 2;
    if (qntAgua < 0) {
        numTripulantes--;
        qntAgua = 0;
    }
    movesRestantes = maxMoves;
}

std::pair<int, int>
CaravanaSecreta::autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros) {
    // Procurar barbaros a 6 posições de distancia
    int alvo = 0, linhaBarbaro, colunaBarbaro;
    int distanciaMin = 999, distancia;
    for (const auto &barbaro: barbaros) {
        distancia = abs(barbaro.getLinha() - linha) +
                    abs(barbaro.getColuna() - coluna);

        if (distancia <= 6) {
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
        int distancia = abs(linha - linhaBarbaro) +
                        abs(coluna - colunaBarbaro);
        int distanciaLinha = abs(linhaBarbaro - linha);
        int distanciaColuna = abs(colunaBarbaro - coluna);
        // Determinar direção para a coluna
        if ((distanciaLinha >= 1 || distanciaColuna >= 1)&& distancia>1) {
            int direcao = rand() % 2;
            if (direcao) { // move coluna primeiro
                if (novaColuna < colunaBarbaro) {
                    novaColuna++;
                } else if (novaColuna > colunaBarbaro) {
                    novaColuna--;
                }
                distancia = abs(novaLinha - linhaBarbaro) +
                            abs(novaColuna - colunaBarbaro);
                if (distancia > 1) {
                    if (novaLinha < linhaBarbaro) {
                        novaLinha++;
                    } else if (novaLinha > linhaBarbaro) {
                        novaLinha--;
                    }
                }
            } else { //move linha primeiro
                if (novaLinha < linhaBarbaro) {
                    novaLinha++;
                } else if (novaLinha > linhaBarbaro) {
                    novaLinha--;
                }
                distancia = abs(novaLinha - linhaBarbaro) +
                            abs(novaColuna - colunaBarbaro);
                if (distancia > 1) {
                    if (novaColuna < colunaBarbaro) {
                        novaColuna++;
                    } else if (novaColuna > colunaBarbaro) {
                        novaColuna--;
                    }
                }
            }
        }
        return std::make_pair(novaLinha, novaColuna);
    }
    int novaLinha = linha + (rand() % 3 - 1);
    int novaColuna = coluna + (rand() % 3 - 1);
    return std::make_pair(novaLinha, novaColuna);
}

std::pair<int, int> CaravanaSecreta::moveMorrer() {
    if (numTripulantes > 0) tipoMovimentacao = 0;
    --instantesRestantes;
    return std::make_pair(linha + (rand() % 3 - 1), coluna + (rand() % 3 - 1));
}

bool CaravanaSecreta::infiltrarBarbaros(std::vector<Barbaro> &barbaros) {
    // TODO alterar chances ser descoberta
    bool encontrou = false;
    for (auto &barbaro: barbaros) {
        int distancia = abs(barbaro.getLinha() - linha) +
                        abs(barbaro.getColuna() - coluna);
        if (distancia == 1) { // Caravana está infiltrada
            encontrou = true;
            int chance = rand() % 4;
            if (chance < 3) {  // 75% chance de matar barbaro
                barbaro.addTripulantes(-1);
                chanceSerDescoberta += 1;
                if (barbaro.getTripulantes() <= 0) {
                    // Barbaros sao destruidos
                    chanceSerDescoberta = 0;
                    std::cout << "Caravana infiltrada " << ID << " matou todos os bárbaros\n";
                    return true;
                }
                std::cout << "Caravana infiltrada " << ID << " matou um barbaro\n";
            } else {           // 25% chance de perder espiao
                --numTripulantes;
                chanceSerDescoberta += 3;
                std::cout << "Caravana infiltrada " << ID << " perdeu um tripulante\n";
            }

            // Limita chance de ser descoberta
            chanceSerDescoberta = std::min(chanceSerDescoberta, 60);

            int serApanhada = rand() % 100+1;
            if (serApanhada < chanceSerDescoberta)
                return false;
            break;
        }
    }
    if (!encontrou) chanceSerDescoberta = 0;
    return true;
// se for apanhada é destruida
// a cada turno chance de 75% de matar 1 barbaro ou perder 1 espiao
// caso um barbaro morra chance de ser apanhada aumenta +1%
}

bool CaravanaSecreta::ataqueTempestade(int probabilidade) {
    if(probabilidade <= 33){
        return true;
    }
    std::cout << "Caravana "<<ID<< " foi apanhada numa tempestade e perdeu " <<floor(numTripulantes * 0.1) <<" tripulantes\n";
    addTripulantes(floor(numTripulantes * -0.1));
    return false;
}