//
// Created by Pedro on 11/3/2024.
//

#include "../include/Utils.h"

// Verifica se uma string representa um número inteiro válido
bool isNumber(const string &str) {
    return !str.empty() && all_of(str.begin(), str.end(), [](char c) { return isdigit(c) || c == '-'; });
}

// Validar comandos
int lerComandos(int fase, Deserto &deserto) {
    cout << "Introduza um comando:" << endl;
    string linha;
    getline(cin, linha);

    linha.erase(0, linha.find_first_not_of(' '));
    linha.erase(linha.find_last_not_of(' ') + 1);

    if (linha.empty()) {
        cout << "[ERRO] Comando vazio\n";
        return fase;
    }

    istringstream sslinha(linha);
    string cmd;
    vector<string> args;

    sslinha >> cmd;
    string arg;
    while (sslinha >> arg) {
        args.push_back(arg);
    }

    if (fase == 1)return processarComandosFase1(cmd, args, deserto);
    else {
        if (deserto.getMoedas() < deserto.getPrecoCaravana() && !deserto.getNumCaravanas()) {
            cout << "Ficou sem caravanas e sem moedas para adquirir mais alguma" << endl;
            cmd = "terminar";
        }
        return processarComandosFase2(cmd, args, deserto);
    }
}

int comandoConfig(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: config <nomeFicheiro>\n";
        return 1; // ERRO Continuar na mesma fase
    }
    if (deserto.lerFicheiro(args[0]))return 2; // Sucesso Passar para fase 2
    return 1; // Falhou Continuar na fase 1
}

int processarComandosFase1(const string &cmd, const vector<string> &args, Deserto &deserto) {
    if (cmd == "config") return comandoConfig(args, deserto); // Ficheiro lido com sucesso passa para fase 2
    else if (cmd == "sair") {
        cout << "Encerrando programa...\n";
        return 0; // Retorna 0 para encerrar programa
    } else {
        cerr << "[ERRO] Comando invalido\n";
    }
    return 1; // Continuar na fase 1
}

int processarComandosFase2(const string &cmd, const vector<string> &args, Deserto &deserto) {
    if (cmd == "exec") comandoExec(args, deserto);
    else if (cmd == "prox") comandoProx(args, deserto);
    else if (cmd == "comprac") comandoComprac(args, deserto);
    else if (cmd == "precos") comandoPrecos(args, deserto);
    else if (cmd == "cidade") comandoCidade(args, deserto);
    else if (cmd == "caravana") comandoCaravana(args, deserto.getCaravanas());
    else if (cmd == "compra") comandoCompra(args, deserto);
    else if (cmd == "vende") comandoVende(args, deserto);
    else if (cmd == "move") comandoMove(args, deserto);
    else if (cmd == "auto") comandoAuto(args, deserto);
    else if (cmd == "stop") comandoStop(args, deserto);
    else if (cmd == "barbaro") comandoBarbaro(args, deserto);
    else if (cmd == "areia") comandoAreia(args, deserto);
    else if (cmd == "moedas") comandoMoedas(args, deserto);
    else if (cmd == "tripul") comandoTripul(args, deserto);
    else if (cmd == "saves") comandoSaves(args, deserto);
    else if (cmd == "loads") comandoLoads(args, deserto);
    else if (cmd == "lists") comandoLists(args, deserto);
    else if (cmd == "dels") comandoDels(args, deserto);
    else if (cmd == "terminar") {
        cout << "Encerrando simulador...\n";
        return 1;
    } else {
        cerr << "[ERRO] Comando nao implementado\n";
    }
    return 2;
}

// Comando: exec <nomeFicheiro>
void comandoExec(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: exec <nomeFicheiro>\n";
        return;
    }
    processarFicheiroComandos(args[0], deserto);
}

// Comando: prox <n>
void comandoProx(const vector<string> &args, Deserto &deserto) {
    if (args.size() > 1 || (args.size() == 1 && !isNumber(args[0]))) {
        cerr << "[ERRO] Sintaxe: prox [<número de instantes>]\n";
        return;
    }
    int instantes = args.empty() ? 1 : stoi(args[0]);
    if (instantes <= 0) {
        cerr << "[ERRO] O número de instantes deve ser maior que 0\n";
        return;
    }
    for (int i = 0; i < instantes; ++i) {
        if (instantes>1)
            cout<<"\nInstante: "<< i <<endl;
        deserto.proxInstante();
        deserto.movimentarBarbaros();
        deserto.atualizarCaravanas();
        deserto.procurarCombates();
        deserto.processarTempestade();
        deserto.atualizarItems();
        deserto.processarCombates();
        deserto.atualizarBarbaros();
        deserto.atualizarBuffer();
        deserto.mostrarMapa(); // para testes
    }
    //deserto.printItems();
}

// Comando: comprac <C> <T>
void comandoComprac(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 2) {
        cerr << "[ERRO] Sintaxe: comprac <cidade> <tipo>\n";
        return;
    }
    char nomeCidade = toupper(args[0][0]);
    char tipo = toupper(args[1][0]);
    if (!isalpha(nomeCidade) || (tipo != 'C' && tipo != 'M' && tipo != 'S')) {
        cerr << "[ERRO] Cidade deve ser uma letra, tipo deve ser C, M ou S\n";
        return;
    }
// Procurar cidade com nome recebido
    for (auto &cidade: deserto.getCidades()) {
        if (cidade.getNome() == nomeCidade) {
            if (cidade.comprarCaravana(tipo)) {
                // Add caravana na mesma posicao da cidade
                deserto.adicionaCaravana(tipo, cidade.getLinha(), cidade.getColuna());
                deserto.ajustarMoedas(-1 * deserto.getPrecoCaravana());
            }
            return;
        }
    }
    std::cerr << "[ERRO] Cidade " << nomeCidade << " nao encontrada\n";
}

// Comando: precos
void comandoPrecos(const vector<string> &args, Deserto &deserto) {
    if (!args.empty()) {
        cerr << "[ERRO] Sintaxe: precos\n";
        return;
    }
    std::cout << "Comprar mercadoria - " << deserto.getPrecoCompraMerc() << " Moedas\nVender mercadoria - "
              << deserto.getPrecoVendaMerc() << " Moedas" << std::endl;
}

// Comando: cidade <C>
void comandoCidade(const vector<string> &args, Deserto &deserto) {
    char nomeCidade = toupper(args[0][0]);
    if (args.size() != 1 || !isalpha(nomeCidade)) {
        cerr << "[ERRO] Sintaxe: cidade <nome cidade>\n";
        return;
    }
    auto &cidades = deserto.getCidades();
    auto &caravanas = deserto.getCaravanas();

    // Procurar cidade com nome recebido
    for (const auto &cidade: cidades) {
        if (cidade.getNome() == nomeCidade) {

            //check if any caravana is in the same position as the city (lin,col)
            std::cout << "Caravanas estacionadas na cidade " << cidade.getNome() << ":";
            for (const auto &caravana: caravanas) {
                if (caravana->getLinha() == cidade.getLinha() &&
                    caravana->getColuna() == cidade.getColuna()) {
                    std::cout << "\n";
                    caravana->detalhes();
                }
            }
            cidade.mostrarCaravanasDisponiveis();
            return;
        }
    }
    std::cerr << "[ERRO] Cidade " << nomeCidade << " nao encontrada\n";
}

// Comando: caravana <C>
void comandoCaravana(const vector<string> &args, const std::vector<std::unique_ptr<Caravana>> &caravanas) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: caravana <número>\n";
        return;
    }
    int id = stoi(args[0]);

    // Procurar caravana com ID lido
    for (const auto &caravana: caravanas) {
        if (caravana->getId() == id) {
            caravana->detalhes();
            return;
        }
    }
    std::cerr << "[ERRO] Caravana " << id << " nao encontrada\n";
}

// Comando: compra <N> <M>
void comandoCompra(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 2 || !isNumber(args[0]) || !isNumber(args[1])) {
        cerr << "[ERRO] Sintaxe: compra <número> <quantidade>\n";
        return;
    }
    int id = stoi(args[0]);
    int quantidade = stoi(args[1]);
    // Procurar caravana com ID lido
    for (const auto &caravana: deserto.getCaravanas()) {
        if (caravana->getId() == id && caravana->estaNaCidade(deserto.getCidades())) {
            if (deserto.getMoedas() >= deserto.getPrecoCompraMerc() * quantidade) {
                if (caravana->carregar(quantidade)) {
                    deserto.ajustarMoedas(-1 * (deserto.getPrecoCompraMerc() * quantidade));
                    std::cout << "Comprou " << quantidade << "T de mercadoria para a caravana " << caravana->getId()
                              << "\n";
                }
            } else std::cerr << "Nao tem moedas suficientes para " << quantidade << "T de mercadoria\n";
            return;
        }
    }
    std::cerr << "[ERRO] Caravana " << id << " nao encontrada\n";
}

// Comando: vende <N>
void comandoVende(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: vende <número>\n";
        return;
    }
    int id = stoi(args[0]);
    // Procurar caravana com ID lido
    for (const auto &caravana: deserto.getCaravanas()) {
        if (caravana->getId() == id && caravana->estaNaCidade(deserto.getCidades())) {
            std::cout << "Vendeu " << caravana->getCarga() << "T de mercadoria\n";
            deserto.ajustarMoedas(caravana->getCarga() * deserto.getPrecoVendaMerc());
            caravana->descarregar();
            return;
        }
    }
    std::cerr << "[ERRO] Caravana " << id << " nao encontrada\n";
}

// Comando: move <N> <X>
void comandoMove(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 2) {
        cerr << "[ERRO] Sintaxe: move <número> <direcao>\n";
        return;
    }

    vector<string> direcoes = {"D", "E", "C", "B", "CE", "CD", "BE", "BD"};
    string dir = args[1];
    std::transform(dir.begin(), dir.end(), dir.begin(), ::toupper);

    if (!isNumber(args[0]) || find(direcoes.begin(), direcoes.end(), dir) == direcoes.end()) {
        cerr << "[ERRO] Sintaxe: move <número> <direcao>\n";
        cerr << "Direcoes validas: D, E, C, B, CE, CD, BE, BD\n";
        return;
    }
    deserto.moverCaravana(stoi(args[0]), dir);
}

// Comando: auto <N>
void comandoAuto(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: auto <número>\n";
        return;
    }
    int id = stoi(args[0]);
    // Procurar caravana com ID lido
    for (const auto &caravana: deserto.getCaravanas()) {
        if (caravana->getId() == id) {
            caravana->setMoveType(1);
            std::cout << "Caravana " << caravana->getId() << " esta em modo automatico\n";
            return;
        }
    }
    std::cerr << "[ERRO] Caravana " << id << " nao encontrada\n";
}

// Comando: stop <N>
void comandoStop(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: stop <número>\n";
        return;
    }
    int id = stoi(args[0]);
    // Procurar caravana com ID lido
    for (const auto &caravana: deserto.getCaravanas()) {
        if (caravana->getId() == id) {
            caravana->setMoveType(0);
            std::cout << "Caravana " << caravana->getId() << " saiu do modo automatico\n";
            return;
        }
    }
    std::cerr << "[ERRO] Caravana " << id << " nao encontrada\n";
}

// Comando: barbaro <l> <c>
void comandoBarbaro(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 2 || !isNumber(args[0]) || !isNumber(args[1])) {
        cerr << "[ERRO] Sintaxe: barbaro <linha> <coluna>\n";
        return;
    }
    int linha = stoi(args[0]);
    int coluna = stoi(args[1]);
    if (linha >= 0 && linha < deserto.getLinhas() && coluna >= 0 && coluna < deserto.getColunas()) {
        if (deserto.verificarMoveAleatorio(linha, coluna)) {
            deserto.adicionaBarbaro(linha, coluna);
            std::cout << "Barbaro adicionado na posicao (" << linha << ", " << coluna << ")\n";
            return;
        }
    }
    cerr << "[ERRO] Posicao invalida\n";
}

// Comando: areia <l> <c> <r>
void comandoAreia(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 3 || !isNumber(args[0]) || !isNumber(args[1]) || !isNumber(args[2])) {
        cerr << "[ERRO] Sintaxe: areia <linha> <coluna> <raio>\n";
        return;
    }
    cout << "Criando tempestade de areia nas coordenadas (" << args[0] << ", " << args[1] << ") com raio " << args[2]
         << "\n";
    deserto.criaTempestade(stoi(args[0]), stoi(args[1]), stoi(args[2]));
}

// Comando: moedas <N>
void comandoMoedas(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: moedas <número>\n";
        return;
    }
    deserto.ajustarMoedas(stoi(args[0]));
}

// Comando: tripul <N> <T>
void comandoTripul(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 2 || !isNumber(args[0]) || !isNumber(args[1])) {
        cerr << "[ERRO] Sintaxe: tripul <número> <quantidade>\n";
        return;
    }
    int id = stoi(args[0]);
    int quantidade = stoi(args[1]);
    // Procurar caravana com ID lido
    for (const auto &caravana: deserto.getCaravanas()) {
        if (caravana->getId() == id && caravana->estaNaCidade(deserto.getCidades())) {
            if (deserto.getMoedas() >= quantidade) {
                if (caravana->addTripulantes(quantidade)) {
                    deserto.ajustarMoedas(-1 * quantidade);
                    std::cout << quantidade << " tripulantes adicionados na caravana " << caravana->getId() << "\n";
                }
            } else std::cerr << "Nao tem moedas suficientes para " << quantidade << " tripulantes\n";
            return;
        }
    }
    std::cerr << "[ERRO] Caravana " << id << " nao encontrada\n";
}

// Comando: saves <nome>
void comandoSaves(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: saves <nome>\n";
        return;
    }
    deserto.saveBuffer(args[0]);
}

// Comando: loads <nome>
void comandoLoads(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: loads <nome>\n";
        return;
    }
    deserto.loadBuffer(args[0]);
}

// Comando: lists
void comandoLists(const vector<string> &args, Deserto &deserto) {
    if (!args.empty()) {
        cerr << "[ERRO] Sintaxe: lists\n";
        return;
    }
    deserto.listBuffer();
}

// Comando: dels <nome>
void comandoDels(const vector<string> &args, Deserto &deserto) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: dels <nome>\n";
        return;
    }
    deserto.apagarBuffer(args[0]);
}

void processarFicheiroComandos(const std::string &filename, Deserto &deserto) {
    std::string folder = "../config/";
    std::string path = folder + filename + ".txt";
    std::ifstream file(path);
    if (!file) {
        std::cerr << "[ERRO] Nao foi possivel abrir o ficheiro: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Remove espaços no início e no final
        line.erase(0, line.find_first_not_of(' '));
        line.erase(line.find_last_not_of(' ') + 1);
        if (line.empty()) continue; // Ignora linhas vazias

        std::istringstream sslinha(line);
        std::string cmd;
        std::vector<std::string> args;

        sslinha >> cmd; // Lê o comando
        std::string arg;
        while (sslinha >> arg) {
            args.push_back(arg); // Armazena os argumentos
        }

        // Processa o comando
        processarComandosFase2(cmd, args, deserto);
    }

    file.close();
    std::cout << "Todos os comandos do ficheiro '" << filename << ".txt' foram processados.\n";
}