//
// Created by Pedro on 11/3/2024.
//

#include "../include/Cidade.h"
#include "../include/Caravana.h"


// Construtor: inicializa as caravanas disponíveis
Cidade::Cidade(char nome, int l, int c) : nome(nome), linha(l), coluna(c) {
    caravanasDisponiveis = {
            {'C', true},
            {'M', true},
            {'S', true}
    };
}
// Mostra as caravanas disponíveis na cidade
void Cidade::mostrarCaravanasDisponiveis() const {
    std::cout << "Caravanas para compra na cidade " << nome << ":\n";
    for (const auto &caravana: caravanasDisponiveis) {
        if (caravana.second)
            std::cout << "\tCaravana  " << converterTipoCaravana(caravana.first) << '\n';
    }
}

// Compra uma caravana, se disponível
bool Cidade::comprarCaravana(char tipo) {
    std::string nomeCaravana = converterTipoCaravana(tipo);
    if (nomeCaravana.empty()) {
        std::cerr << "[ERRO] Tipo de caravana inválido. <C>-Comercio <M>-Militar <S>-Secreta \n";
        return false;
    }

    auto it = caravanasDisponiveis.find(tipo); // Procura pelo tipo (chave do map)
    if (it != caravanasDisponiveis.end() && it->second) {
        it->second = false; // Marca a caravana como comprada

        std::cout << "Caravana " << nomeCaravana
                  << " comprada na cidade " << nome << std::endl;
        return true;
    }

    std::cerr << "[ERRO] Caravana " << nomeCaravana
              << " não está disponível na cidade " << nome << std::endl;
    return false;
}
