//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_DESERTO_H
#define SIMDESERTO_DESERTO_H
#include <memory>
#include <limits>

#include "Buffer.h"
#include "Caravana.h"
#include "Cidade.h"
#include "Caravanas/CaravanaSecreta.h"
#include "Caravanas/CaravanaMilitar.h"
#include "Caravanas/CaravanaComercio.h"
#include "Barbaro.h"

class Deserto {
private:
    // Valores Configuraveis
    int moedas, instantesEntreNovosItems, duracaoItem, maxItems, precoVendaMerc, precoCompraMerc;
    int precoCaravana, instantesEntreNovosBarbaros, duracaoBarbaros;
    int numCidades = 0, numCaravanas = 0;
    int linhas, colunas;
    Buffer buffer;
    std::map<std::string, Buffer> bufferSaves; // Nome e cópia do buffer
    std::vector<std::unique_ptr<Caravana>> caravanas;
    std::vector<Cidade> cidades;
    std::vector<std::pair<int, int>> montanhas;
    std::vector<Barbaro> barbaros;
public:
    Deserto(const Buffer &bufferInicial); // Construtor
    ~Deserto() = default;

    bool lerFicheiro(const std::string &filename); // Carrega a config de um ficheiro
    void mostrarMapa() const;                   // Exibe o mapa na consola
    void mostrarMapa(Buffer buffer) const;

    bool saveBuffer(const std::string &nome);
    bool loadBuffer(const std::string &nome);
    void listBuffer() const;
    bool apagarBuffer(const std::string &nome);

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
    int getNumCaravanas() const;

    int getMoedas() const;

    int getPrecoCaravana() const;
    int getPrecoCompraMerc() const;
    int getPrecoVendaMerc() const;

    void processarBuffer();
    void atualizarBuffer();

    const std::vector<std::pair<int, int>>& getMontanhas() const;

    void adicionaCidade(char nome, int linha, int coluna);
    void printCidades() const;
    const std::vector<Cidade>& getCidades() const; // Const
    std::vector<Cidade>& getCidades(); //Nao const, para poder fazer alteracoes

    void adicionaCaravana(char tipo, int l, int c);
    void printCaravanas() const;
    const std::vector<std::unique_ptr<Caravana>>& getCaravanas() const;

    void moverCaravana(int id, const std::string& movimento);
    bool movimentoInvalido(int linha, int coluna);
    void atualizarCaravanas();

    const std::vector<Barbaro>& getBarbaros();
    void movimentarBarbaros();
    bool verificarMoveAleatorio(int &novaLinha, int &novaColuna);
};


#endif // SIMDESERTO_DESERTO_H
