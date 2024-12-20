#ifndef SIMDESERTO_CARAVANA_H
#define SIMDESERTO_CARAVANA_H

#include <iostream>

class Caravana {
protected:
    static int nextID; // Para gerar IDs únicos
    int ID, numTripulantes, qntAgua, qntMerc;
    const int cargaMaxima, aguaMax, tripulantesMax;
    int tipoMovimentacao; // 0-Sem tripulantes, 1-Utilizador, 2-Autónomo
    int linha, coluna;
    char tipo; // c -> comercio, m -> militar, s -> secreto

public:
    Caravana(int cargaMax, int aguaMax, int tripulantesMax, int tipoMov, int linha, int coluna);
    virtual ~Caravana();

    // Getters
    int getId() const { return ID; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    char getTipo() const { return tipo; }
    int getCarga() const { return qntMerc; }

    void detalhes() const;

    void mover(int novaLinha, int novaColuna) {
        linha = novaLinha;
        coluna = novaColuna;
    }

    void carregar(int quantidade) {
        if(qntMerc <= cargaMaxima)
            qntMerc += quantidade;
        //else
            //Carga maxima atingida!!
    }

    void reabasteceAgua(){
        qntAgua = aguaMax;
    }

    void descarregar() {
        qntMerc = 0;
    }

};

std::string converterTipoCaravana(char tipo);
#endif //SIMDESERTO_CARAVANA_H