#ifndef SIMDESERTO_CARAVANA_H
#define SIMDESERTO_CARAVANA_H

#include <iostream>
#include <vector>
#include <memory>
#include "Cidade.h"
#include "Barbaro.h"

class Caravana {
protected:
    static int nextID; // Para gerar IDs únicos
    int ID, numTripulantes, qntAgua, qntMerc;
    const int cargaMaxima, aguaMax, tripulantesMax;
    int movesRestantes, maxMoves, tipoMovimentacao; // 0-Utilizador, 1-Sem tripulantes, 2-Autónomo
    int linha, coluna;
    int instantesRestantes;
    char tipo; // c -> comercio, m -> militar, s -> secreto
    std::pair<int, int> posAnterior;

public:
    Caravana(int cargaMax, int aguaMax, int tripulantesMax, int tipoMov, int maxMoves, int linha, int coluna);
    static void resetID() { nextID = 1; }
    virtual ~Caravana();

    virtual void atualizarTurno() = 0; // Método virtual puro
    virtual std::pair<int, int> autoMove(std::vector<std::unique_ptr<Caravana>> &caravanas, std::vector<Barbaro> &barbaros) = 0;

    // Getters
    int getId() const { return ID; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    char getTipo() const { return tipo; }
    int getCarga() const { return qntMerc; }
    int getMoves() { return movesRestantes; }
    int getTipoMovimentacao() const { return tipoMovimentacao; }

    void detalhes() const;

    void mover(int novaLinha, int novaColuna);
    void setMoveType(int moveType){
        tipoMovimentacao = moveType;
    }


    void reabasteceAgua(){
        qntAgua = aguaMax;
    }

    bool carregar(int quantidade);
    void descarregar() {
        qntMerc = 0;
    }

    bool addTripulantes(int quantidade);

    bool estaNaCidade(const std::vector<Cidade>& cidades) const;
    bool estaNaCidade(char nomeCidade, const std::vector<Cidade>& cidades) const;

};

std::string converterTipoCaravana(char tipo);
#endif //SIMDESERTO_CARAVANA_H