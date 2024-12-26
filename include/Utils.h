//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_UTILS_H
#define SIMDESERTO_UTILS_H

#include "Deserto.h"


using namespace std;

class Position{
    int x, y;
};

// Verifica se uma string representa um número inteiro válido
bool isNumber(const string &str);

// Função principal para ler comandos do usuário
int lerComandos(int fase, Deserto& deserto);

// Processa o comando e chama a função correspondente
int processarComandosFase1(const string &cmd, const vector<string> &args, Deserto& deserto);

int processarComandosFase2(const string &cmd, const vector<string> &args, Deserto& deserto);


// Funções para cada comando
int comandoConfig(const vector<string> &args, Deserto& deserto);

void comandoExec(const vector<string> &args, Deserto &deserto);
void processarFicheiroComandos(const std::string &filename, Deserto &deserto);

void comandoProx(const vector<string> &args, Deserto& deserto);

void comandoComprac(const vector<string> &args, Deserto &deserto);

void comandoPrecos(const vector<string> &args, Deserto &deserto);

void comandoCidade(const vector<string> &args, Deserto &deserto);

void comandoCaravana(const vector<string>& args, const std::vector<std::unique_ptr<Caravana>>& caravanas);

void comandoCompra(const vector<string> &args, Deserto &deserto);

void comandoVende(const vector<string> &args, Deserto &deserto);

void comandoMove(const vector<string> &args, Deserto& deserto);

void comandoAuto(const vector<string> &args, Deserto& deserto);

void comandoStop(const vector<string> &args, Deserto& deserto);

void comandoBarbaro(const vector<string> &args, Deserto &deserto);

void comandoAreia(const vector<string> &args, Deserto &deserto);

void comandoMoedas(const vector<string> &args, Deserto& deserto);

void comandoTripul(const vector<string> &args, Deserto &deserto);

void comandoSaves(const vector<string> &args, Deserto &deserto);

void comandoLoads(const vector<string> &args, Deserto &deserto);

void comandoLists(const vector<string> &args, Deserto &deserto);

void comandoDels(const vector<string> &args, Deserto &deserto);

#endif //SIMDESERTO_UTILS_H
