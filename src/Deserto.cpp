//
// Created by Pedro on 11/3/2024.
//

#include "../include/Deserto.h"

// Construtor: inicializa o mapa com pontos (.)

Deserto::Deserto(Buffer buffer) : buffer(buffer) {}


// Lê a config de um ficheiro
bool Deserto::lerFicheiro(const std::string &filename) {
    std::string folder = "../config/";
    std::string path = folder + filename;

    std::ifstream file(path);
    if (!file) {
        std::cerr << "Erro ao abrir o ficheiro: " << filename << std::endl;
        return false;
    }

    std::string lixo;
    int nLinhas, nColunas;

    // Ler as primeiras duas linhas com os tamanhos
    file >> lixo >> nLinhas;
    buffer.setLinhas(nLinhas);
    std::cout << "Linhas: " << nLinhas << std::endl;

    file >> lixo >> nColunas;
    buffer.setColunas(nColunas);
    std::cout << "Colunas: " << nColunas << std::endl;

    // Validar valores de linhas e colunas
    if (nLinhas <= 0 || nColunas <= 0) {
        std::cerr << "Erro: Configuração inválida para linhas ou colunas." << std::endl;
        return false;
    }


       //mapa.resize(nLinhas * nColunas, ' ');
    // Ler cada linha do mapa
    std::string line;
    for (int i = 0; i <= nLinhas && std::getline(file, line); ++i) {
        for (int j = 0; j < std::min(nColunas, static_cast<int>(line.size())); ++j) {
            //mapa[calcularIndice(i - 1, j)] = line[j];
            buffer.moveCursor(i, j);
            buffer.writeChar(line[j]);
        }

    }
    buffer.print();
    //mostrarMapa();

    // Ler valores configuráveis
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string chave;
        int valor;

        // Aplicar o valor à configuração correspondente
        if (iss >> chave >> valor) {
            if (chave == "moedas") {
                setMoedas(valor);
                std::cout << "Moedas configuradas: " << valor << std::endl;
            } else if (chave == "instantes_entre_novos_itens") {
                setInstantesEntreNovosItems(valor);
                std::cout << "Instantes entre novos items: " << valor << std::endl;
            } else if (chave == "duração_item") {
                setDuracaoItem(valor);
                std::cout << "Duração do item: " << valor << std::endl;
            } else if (chave == "max_itens") {
                setMaxItens(valor);
                std::cout << "Máximo de itens: " << valor << std::endl;
            } else if (chave == "preço_venda_mercadoria") {
                setPrecoVendaMerc(valor);
                std::cout << "Preço de venda de mercadoria: " << valor << std::endl;
            } else if (chave == "preço_compra_mercadoria") {
                setPrecoCompraMerc(valor);
                std::cout << "Preço de compra de mercadoria: " << valor << std::endl;
            } else if (chave == "preço_caravana") {
                setPrecoCaravana(valor);
                std::cout << "Preço da caravana: " << valor << std::endl;
            } else if (chave == "instantes_entre_novos_barbaros") {
                setInstantesEntreNovosBarbaros(valor);
                std::cout << "Instantes entre novos bárbaros: " << valor << std::endl;
            } else if (chave == "duração_barbaros") {
                setDuracaoBarbaros(valor);
                std::cout << "Duração dos bárbaros: " << valor << std::endl;
            } else {
                std::cerr << "Aviso: Configuração desconhecida '" << chave << "'" << std::endl;
            }
        } else {
            std::cerr << "Erro ao ler linha de configuração: " << line << std::endl;
        }
    }
    return true;
}

// Mostra o mapa na consola






void Deserto::setTerreno(int linha, int coluna, char terreno) {

}

void Deserto::setMoedas(int valor) {
    this->moedas = valor;
}

void Deserto::setInstantesEntreNovosItems(int valor) {
    this->instantesEntreNovosItems = valor;
}

void Deserto::setDuracaoItem(int valor) {
    this->duracaoItem = valor;
}

void Deserto::setMaxItens(int valor) {
    this->maxItems = valor;
}

void Deserto::setPrecoVendaMerc(int valor) {
    this->precoVendaMerc = valor;
}

void Deserto::setPrecoCompraMerc(int valor) {
    this->precoCompraMerc = valor;
}

void Deserto::setPrecoCaravana(int valor) {
    this->precoCaravana = valor;
}

void Deserto::setInstantesEntreNovosBarbaros(int valor) {
    this->instantesEntreNovosBarbaros = valor;
}

void Deserto::setDuracaoBarbaros(int valor) {
    this->duracaoBarbaros = valor;
}

int Deserto::getNumCaravanas() {
    return numCaravanas;
}

int Deserto::getMoedas() {
    return moedas;
}

int Deserto::getPrecoCaravana() {
    return precoCaravana;
}

void Deserto::ajustarMoedas(int valor) {
    moedas += valor;
    std::cout << valor <<" moedas adicionadas\nMoedas totais: " << moedas << std::endl;
}
