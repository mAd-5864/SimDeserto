//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_DESERTO_H
#define SIMDESERTO_DESERTO_H
#include <limits>
#include <cmath>

#include "Buffer.h"
#include "Caravana.h"
#include "Cidade.h"
#include "Caravanas/CaravanaSecreta.h"
#include "Caravanas/CaravanaMilitar.h"
#include "Caravanas/CaravanaComercio.h"
#include "Barbaro.h"
#include "Item.h"
#include "Tempestade.h"

class Deserto {
private:
    // Valores Configuraveis
    int moedas, instantesEntreNovosItems, duracaoItem, maxItems, precoVendaMerc, precoCompraMerc;
    int precoCaravana, instantesEntreNovosBarbaros, duracaoBarbaros;
    int numCidades = 0, numCaravanas = 0, numeroItens = 0;
    int linhas, colunas, instanteAtual = 0;
    Buffer buffer;
    std::map<std::string, Buffer> bufferSaves; // Nome e cópia do buffer
    std::vector<std::unique_ptr<Caravana>> caravanas;
    std::vector<Cidade> cidades;
    std::vector<std::pair<int, int>> montanhas;
    std::vector<Barbaro> barbaros;
    std::vector<std::pair<int, int>> combates; // <id_Caravana, id_Barbaro>
    std::vector<Item> itens;
    std::vector<Tempestade> tempestades;
public:
    Deserto(const Buffer &bufferInicial); // Construtor
    ~Deserto();

    bool lerFicheiro(const std::string &filename); // Carrega a config de um ficheiro
    void mostrarMapa() const;                   // Exibe o mapa na consola
    void mostrarMapa(Buffer buffer) const;

    bool saveBuffer(const std::string &nome);
    bool loadBuffer(const std::string &nome);
    void listBuffer() const;
    bool apagarBuffer(const std::string &nome);

    void setLinhas(int linhas);
    void setColunas(int colunas);
    int getLinhas() { return linhas; }
    int getColunas() { return colunas; }

    void proxInstante() { ++instanteAtual; };
    int getInstante() { return instanteAtual; }

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

    const std::vector<std::pair<int, int>> &getMontanhas() const;

    void adicionaCidade(char nome, int linha, int coluna);
    const std::vector<Cidade> &getCidades() const; // Const
    std::vector<Cidade> &getCidades(); //Nao const, para poder fazer alteracoes

    void adicionaCaravana(char tipo, int l, int c);
    void printCaravanas() const;
    const std::vector<std::unique_ptr<Caravana>> &getCaravanas() const;

    void moverCaravana(int id, const std::string &movimento);
    bool movimentoInvalido(int linha, int coluna);
    void atualizarCaravanas();

    void adicionaBarbaro(int linha, int coluna);
    const std::vector<Barbaro> &getBarbaros();
    void atualizarBarbaros();
    void movimentarBarbaros();
    bool verificarMoveAleatorio(int &novaLinha, int &novaColuna);
    bool perseguirCaravana(Barbaro &barbaro, int destinoLinha, int destinoColuna);

    void processarCombates();

    void printItems() const;
    void adicionaItem(int linha, int coluna, int tipo);
    void atualizarItems();
    std::pair<int, int> procuraItem(int linha, int coluna);
    template <typename Entity>
    bool processarItem(Entity& entity, int itemTipo, int maxTripulantes);

    void criaTempestade(int linha, int coluna, int raio);
    void processarTempestade();

    void procurarCombates();
};

#endif // SIMDESERTO_DESERTO_H
