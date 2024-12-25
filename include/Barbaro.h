
#ifndef SIMDESERTO_BARBARO_H
#define SIMDESERTO_BARBARO_H

#include <cstdlib> // For random number generation
#include <iostream> // Para mensagens de depuração
#include <vector>

class Barbaro {
    static int nextID; // Para gerar IDs únicos
    int ID, linha, coluna;
    int turnosRestantes, maxTripulantes, numTripulantes;
public:
    Barbaro(int lin, int col, int maxTripulantes, int turnosRestantes);

    int getId() const { return ID; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    int getTripulantes() const { return numTripulantes; }
    void addTripulantes(int quantidade) {
        if (numTripulantes + quantidade <= 40) {
            numTripulantes += quantidade;
        }
    }

    bool atualizar();
    bool estaAborrecido() const { return !turnosRestantes; }
    void move(int novaLinha, int novaColuna);
    bool perseguirCaravana(int destinoLinha, int destinoColuna);
};

#endif // SIMDESERTO_BARBARO_H