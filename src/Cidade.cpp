//
// Created by Pedro on 11/3/2024.
//

#include "../include/Cidade.h"
#include "../include/Caravana.h"


// Construtor: inicializa as caravanas disponíveis
Cidade::Cidade(char nome, int l, int c) : nome(nome), linha(l), coluna(c) {
    caravanasDisponiveis = {
            {"Mercadoria", true},
            {"Militar",    true},
            {"Secreta",    true}
    };
}

// Mostra as caravanas disponíveis na cidade
void Cidade::mostrarCaravanasDisponiveis() const {
    std::cout << "Caravanas disponíveis na cidade " << nome << ":\n";
    for (const auto &caravana: caravanasDisponiveis) {
        std::cout << "  " << caravana.first << " - " << (caravana.second ? "Disponível" : "Indisponível") << '\n';
    }
}

// Compra uma caravana, se disponível
bool Cidade::comprarCaravana(char tipo) {
    std::string nomeCaravana = converterTipoCaravana(tipo);
    if (nomeCaravana.empty()) {
        std::cerr << "[ERRO] Tipo de caravana inválido. <C>-Comercio <M>-Militar <S>-Secreta \n";
        return false;
    }

    auto it = caravanasDisponiveis.find(nomeCaravana);
    if (it != caravanasDisponiveis.end() && it->second) {
        it->second = false; // Marca a caravana como comprada
        //chamar adicionaCaravana
        std::cout << "Caravana do tipo " << nomeCaravana << " comprada na cidade " << nome << std::endl;
        return true;
    }

    std::cerr << "[ERRO] Caravana do tipo " << nomeCaravana
              << " não está disponível na cidade " << nome << std::endl;
    return false;
}
