#ifndef SIMDESERTO_CARAVANA_H
#define SIMDESERTO_CARAVANA_H

#include "Utils.h"


class Caravana {
protected:
    int ID, numTripulantes, qntAgua, qntMerc;
    const int cargaMaxima, aguaMax;
    int tipoMovimentacao; // 0-Sem tripulantes, 1-Utilizador, 2-Autónomo
    int linha, coluna;
    char tipo; // c -> comercio, m -> militar, s -> secreto

public:
    Caravana(int cargaMax, int aguaMax, int tipoMov, int linha, int coluna);
    virtual ~Caravana();

    // Common methods (add getters, setters, or virtual methods here if needed)
    int getId() const { return ID; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    char getTipo() const { return tipo; }
    int getCarga() const { return qntMerc; }

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

    void mostrarDetalhes() const {
        std::cout << "Caravana " << ID
                  << " [Tipo: " << tipo
                  << ", Posição: (" << linha << ", " << coluna << ")"
                  << ", Carga: " << qntMerc << "]\n";
    }
};
#endif //SIMDESERTO_CARAVANA_H