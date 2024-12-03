//
// Created by Pedro on 11/3/2024.
//

#include "../include/Utils.h"
#include "../include/Deserto.h"

// Verifica se uma string representa um número inteiro válido
bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), [](char c) { return isdigit(c) || c == '-'; });
}

// Validar comandos
int lerComandos(int fase, Deserto& deserto) {
    cout << "Introduza um comando:\n";

    int x = 0;
    string linha;
    getline(cin, linha);

    // Remover espaços no início e final da string
    linha.erase(0, linha.find_first_not_of(' '));
    linha.erase(linha.find_last_not_of(' ') + 1);

    if (linha.empty()) {
        cout << "[ERRO] Comando vazio\n";
        return -1;
    }

    // Separar comando e argumentos
    istringstream sslinha(linha);
    string cmd;
    vector<string> args;

    sslinha >> cmd; // Lê o comando
    string arg;
    while (sslinha >> arg) {
        args.push_back(arg); // Armazena os argumentos
    }

    // Processar o comando
    if (fase == 1) {
        return processarComandosFase1(cmd, args, deserto);
    } else {
        if (deserto.getMoedas()<deserto.getPrecoCaravana() || !deserto.getNumCaravanas()) return 0;
        return processarComandosFase2(cmd, args, deserto);
    }
}
int comandoConfig(const vector<string>& args, Deserto& deserto){
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: config <nomeFicheiro>\n";
        return 1;
    }
    if (deserto.lerFicheiro(args[0])) return 2;
    return 1;
}

int processarComandosFase1(const string& cmd, const vector<string>& args, Deserto& deserto) {
    if (cmd == "config") return comandoConfig(args, deserto);
    else if (cmd == "sair") {
        cout << "Encerrando programa...\n";
        exit(1);
    } else {
        cout << "[ERRO] Comando inválido\n";
    }
    return 1;
}

int processarComandosFase2(const string& cmd, const vector<string>& args, Deserto& deserto) {
    if (cmd == "exec") comandoExec(args);
    else if (cmd == "prox") comandoProx(args, deserto);
    else if (cmd == "comprac") comandoComprac(args);
    else if (cmd == "precos") comandoPrecos(args);
    else if (cmd == "cidade") comandoCidade(args);
    else if (cmd == "caravana") comandoCaravana(args);
    else if (cmd == "compra") comandoCompra(args);
    else if (cmd == "vende") comandoVende(args);
    else if (cmd == "move") comandoMove(args);
    else if (cmd == "auto") comandoAuto(args);
    else if (cmd == "stop") comandoStop(args);
    else if (cmd == "barbaro") comandoBarbaro(args);
    else if (cmd == "areia") comandoAreia(args);
    else if (cmd == "moedas") comandoMoedas(args);
    else if (cmd == "tripul") comandoTripul(args);
    else if (cmd == "saves") comandoSaves(args);
    else if (cmd == "loads") comandoLoads(args);
    else if (cmd == "lists") comandoLists(args);
    else if (cmd == "dels") comandoDels(args);
    else if (cmd == "terminar") {
        cout << "Encerrando simulador...\n";
        return 1;
    } else {
        cout << "[ERRO] Comando nao implementado\n";
    }
    return 2;
}


// Comando: exec <nomeFicheiro>
void comandoExec(const vector<string>& args) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: exec <nomeFicheiro>\n";
        return;
    }
    cout << "Executando comandos do ficheiro: " << args[0] << "\n";
    // Implementar execução de comandos do ficheiro
}

// Comando: prox <n>
void comandoProx(const vector<string>& args, Deserto& deserto) {
    if (args.size() > 1 || (args.size() == 1 && !isNumber(args[0]))) {
        cerr << "[ERRO] Sintaxe: prox [<número de instantes>]\n";
        return;
    }
    int instantes = args.empty() ? 1 : stoi(args[0]);
    if (instantes <= 0) {
        cerr << "[ERRO] O número de instantes deve ser maior que 0.\n";
        return;
    }
    cout << "Avançando " << instantes << " instante(s).\n";
    // Implementar avanço de instantes
}

// Comando: comprac <C> <T>
void comandoComprac(const vector<string>& args) {
    if (args.size() != 2) {
        cerr << "[ERRO] Sintaxe: comprac <cidade> <tipo>\n";
        return;
    }
    char cidade = args[0][0];
    char tipo = args[1][0];
    if (!isalpha(cidade) || (tipo != 'C' && tipo != 'M' && tipo != 'S')) {
        cerr << "[ERRO] Cidade deve ser uma letra, tipo deve ser C, M ou S.\n";
        return;
    }
    cout << "Comprando caravana do tipo " << tipo << " na cidade " << cidade << ".\n";
    // Implementar compra de caravana
}

// Comando: precos
void comandoPrecos(const vector<string>& args) {
    if (!args.empty()) {
        cerr << "[ERRO] Sintaxe: precos\n";
        return;
    }
    cout << "Listando preços das mercadorias.\n";
    // Implementar listagem de preços
}

// Comando: cidade <C>
void comandoCidade(const vector<string>& args) {
    if (args.size() != 1 || !isalpha(args[0][0])) {
        cerr << "[ERRO] Sintaxe: cidade <cidade>\n";
        return;
    }
    cout << "Listando conteúdo da cidade: " << args[0] << ".\n";
    // Implementar listagem de conteúdo da cidade
}

// Comando: caravana <C>
void comandoCaravana(const vector<string>& args) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: caravana <número>\n";
        return;
    }
    cout << "Mostrando detalhes da caravana: " << args[0] << ".\n";
    // Implementar detalhes da caravana
}

// Comando: compra <N> <M>
void comandoCompra(const vector<string>& args) {
    if (args.size() != 2 || !isNumber(args[0]) || !isNumber(args[1])) {
        cerr << "[ERRO] Sintaxe: compra <número> <quantidade>\n";
        return;
    }
    cout << "Comprando " << args[1] << " toneladas de mercadoria para a caravana " << args[0] << ".\n";
    // Implementar compra de mercadoria
}

// Comando: vende <N>
void comandoVende(const vector<string>& args) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: vende <número>\n";
        return;
    }
    cout << "Vendendo mercadoria da caravana: " << args[0] << ".\n";
    // Implementar venda de mercadoria
}

// Comando: move <N> <X>
void comandoMove(const vector<string>& args) {
    vector<string> direcoes = {"D", "E", "C", "B", "CE", "CD", "BE", "BD"};
    if (args.size() != 2 || !isNumber(args[0]) || find(direcoes.begin(), direcoes.end(), args[1]) == direcoes.end()) {
        cerr << "[ERRO] Sintaxe: move <número> <direção>\n";
        cerr << "Direções válidas: D, E, C, B, CE, CD, BE, BD\n";
        return;
    }
    cout << "Movendo caravana " << args[0] << " para a direção " << args[1] << ".\n";
    // Implementar movimentação de caravana
}

// Comando: auto <N>
void comandoAuto(const vector<string>& args) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: auto <número>\n";
        return;
    }
    cout << "Ativando modo automático para a caravana: " << args[0] << ".\n";
    // Implementar modo automático
}

// Comando: stop <N>
void comandoStop(const vector<string>& args) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: stop <número>\n";
        return;
    }
    cout << "Desativando modo automático para a caravana: " << args[0] << ".\n";
    // Implementar desativação do modo automático
}

// Comando: barbaro <l> <c>
void comandoBarbaro(const vector<string>& args) {
    if (args.size() != 2 || !isNumber(args[0]) || !isNumber(args[1])) {
        cerr << "[ERRO] Sintaxe: barbaro <linha> <coluna>\n";
        return;
    }
    cout << "Criando caravana bárbara nas coordenadas (" << args[0] << ", " << args[1] << ").\n";
    // Implementar criação de bárbaros
}

// Comando: areia <l> <c> <r>
void comandoAreia(const vector<string>& args) {
    if (args.size() != 3 || !isNumber(args[0]) || !isNumber(args[1]) || !isNumber(args[2])) {
        cerr << "[ERRO] Sintaxe: areia <linha> <coluna> <raio>\n";
        return;
    }
    cout << "Criando tempestade de areia nas coordenadas (" << args[0] << ", " << args[1] << ") com raio " << args[2] << ".\n";
    // Implementar tempestade de areia
}

// Comando: moedas <N>
void comandoMoedas(const vector<string>& args) {
    if (args.size() != 1 || !isNumber(args[0])) {
        cerr << "[ERRO] Sintaxe: moedas <número>\n";
        return;
    }
    cout << "Ajustando moedas em " << args[0] << ".\n";
    // Implementar ajuste de moedas
}

// Comando: tripul <N> <T>
void comandoTripul(const vector<string>& args) {
    if (args.size() != 2 || !isNumber(args[0]) || !isNumber(args[1])) {
        cerr << "[ERRO] Sintaxe: tripul <número> <quantidade>\n";
        return;
    }
    cout << "Adicionando " << args[1] << " tripulantes à caravana " << args[0] << ".\n";
    // Implementar adição de tripulantes
}

// Comando: saves <nome>
void comandoSaves(const vector<string>& args) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: saves <nome>\n";
        return;
    }
    cout << "Salvando estado visual com o nome: " << args[0] << ".\n";
    // Implementar save visual
}

// Comando: loads <nome>
void comandoLoads(const vector<string>& args) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: loads <nome>\n";
        return;
    }
    cout << "Carregando estado visual com o nome: " << args[0] << ".\n";
    // Implementar load visual
}

// Comando: lists
void comandoLists(const vector<string>& args) {
    if (!args.empty()) {
        cerr << "[ERRO] Sintaxe: lists\n";
        return;
    }
    cout << "Listando todos os estados visuais salvos.\n";
    // Implementar listagem de estados visuais
}

// Comando: dels <nome>
void comandoDels(const vector<string>& args) {
    if (args.size() != 1) {
        cerr << "[ERRO] Sintaxe: dels <nome>\n";
        return;
    }
    cout << "Excluindo estado visual com o nome: " << args[0] << ".\n";
    // Implementar exclusão de estado visual
}
