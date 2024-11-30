//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_DESERTO_H
#define SIMDESERTO_DESERTO_H

#include "Utils.h"

class Deserto
{
private:
    int linhas, colunas;    // Dimensões do mapa
    std::vector<char> mapa; // Vetor para o mapa
    int calcularIndice(int linha, int coluna) const; // Calcula o índice no vetor para linha e coluna
    // Valores Configuraveis
    int moedas, instantesEntreNovosItems, duracaoItem, maxItems, precoVendaMerc, precoCompraMerc;
    int precoCaravana, instantesEntreNovosBarbaros, duracaoBarbaros;
public:
    Deserto(int linhas, int colunas); // Construtor
    ~Deserto() = default;

    bool lerFicheiro(const std::string &filename); // Carrega a config de um ficheiro
    void mostrarMapa() const;                       // Exibe o mapa na consola

    void setLinhas(int linhas);
    void setColunas(int colunas);
    char getTerreno(int linha, int coluna) const;         // Obtem o terreno de uma posição
    void setTerreno(int linha, int coluna, char terreno); // Define o terreno de uma posição
    void setMoedas(int valor);

    void setInstantesEntreNovosItems(int valor);

    void setDuracaoItem(int valor);

    void setDuracaoBarbaros(int valor);

    void setMaxItens(int valor);

    void setPrecoVendaMerc(int valor);

    void setPrecoCompraMerc(int valor);

    void setPrecoCaravana(int valor);

    void setInstantesEntreNovosBarbaros(int valor);
};

#endif // SIMDESERTO_DESERTO_H
