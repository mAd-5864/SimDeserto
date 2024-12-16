//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_DESERTO_H
#define SIMDESERTO_DESERTO_H

#include "Buffer.h"

class Deserto {
private:
    // Valores Configuraveis
    int moedas, instantesEntreNovosItems, duracaoItem, maxItems, precoVendaMerc, precoCompraMerc;
    int precoCaravana, instantesEntreNovosBarbaros, duracaoBarbaros, numCaravanas = 0;
    Buffer buffer;
public:
    Deserto(const Buffer& bufferInicial); // Construtor
    ~Deserto() = default;

    bool lerFicheiro(const std::string &filename); // Carrega a config de um ficheiro
    void mostrarMapa() const;                   // Exibe o mapa na consola
    void mostrarMapa(Buffer buffer) const;

    void setLinhas(int linhas);

    void setColunas(int colunas);

    char getTerreno(int linha, int coluna) const;         // Obtem o terreno de uma posição
    void setTerreno(int linha, int coluna, char terreno); // Define o terreno de uma posição
    void setMoedas(int valor);
    void ajustarMoedas(int valor);

    void setInstantesEntreNovosItems(int valor);

    void setDuracaoItem(int valor);

    void setDuracaoBarbaros(int valor);

    void setMaxItens(int valor);

    void setPrecoVendaMerc(int valor);

    void setPrecoCompraMerc(int valor);

    void setPrecoCaravana(int valor);

    void setInstantesEntreNovosBarbaros(int valor);

    // Getters
    int getNumCaravanas();
    int getMoedas();
    int getPrecoCaravana();
};


#endif // SIMDESERTO_DESERTO_H
