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
    }else qntAgua -= 2;
    if (qntAgua < 0) {
        numTripulantes--;
        qntAgua = 0;
    }
    movesRestantes = maxMoves;
}

std::pair<int, int> CaravanaSecreta::autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros){
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
    int novaLinha = linha + (rand() % 3 - 1);
    int novaColuna = coluna + (rand() % 3 - 1);
    return std::make_pair(novaLinha, novaColuna);
}

std::pair<int, int> CaravanaSecreta::moveMorrer() {
    if (numTripulantes > 0) tipoMovimentacao = 0;
    --instantesRestantes;
    return std::make_pair(linha + (rand() % 3 - 1), coluna + (rand() % 3 - 1));
}

bool CaravanaSecreta::infiltrarBarbaros(std::vector<Barbaro> &barbaros){
    for (auto barbaro = barbaros.begin(); barbaro != barbaros.end();) {
        int distancia = abs(barbaro->getLinha() - linha) +
                    abs(barbaro->getColuna() - coluna);
        if (distancia==1){ // Caravana está infiltrada
            std::cout<<"entrou 2.1\n";
            int chance = rand() % 4;
            if (chance < 3) {  // 75% chance de matar barbaro
                barbaro->addTripulantes(-1);
                chanceSerDescoberta+=2;
                if (barbaro->getTripulantes()<=0){
                    // Barbaros sao destruidos
                    chanceSerDescoberta=0;
                    std::cout << "Caravana infiltrada " << ID << " infiltrou com sucesso os barbaros\n";
                    return true;
                }
            } else {           // 25% chance de perder espiao
                --numTripulantes;
                chanceSerDescoberta+=5;
            }
            int serApanhada = rand() %100;
            if (serApanhada<chanceSerDescoberta)
                return false;
        }
    }
    return true;
// se for apanhada é destruida
// a cada turno chance de 75% de matar 1 barbaro ou perder 1 espiao
// caso um barbaro morra chance de ser apanhada aumenta +2%
}

int CaravanaSecreta::ataqueTempestade(int probabilidade) {
    if(probabilidade <= 33){
        return 1;
    }
    retiraTripulantes(10);
    return 0;
}