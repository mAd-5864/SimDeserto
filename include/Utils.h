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

void comandoExec(const vector<string> &args);

void comandoProx(const vector<string> &args, Deserto& deserto);

void comandoComprac(const vector<string> &args);

void comandoPrecos(const vector<string> &args);

void comandoCidade(const vector<string> &args);

void comandoCaravana(const vector<string> &args);

void comandoCompra(const vector<string> &args);

void comandoVende(const vector<string> &args);

void comandoMove(const vector<string> &args);

void comandoAuto(const vector<string> &args);

void comandoStop(const vector<string> &args);

void comandoBarbaro(const vector<string> &args);

void comandoAreia(const vector<string> &args);

void comandoMoedas(const vector<string> &args, Deserto& deserto);

void comandoTripul(const vector<string> &args);

void comandoSaves(const vector<string> &args);

void comandoLoads(const vector<string> &args);

void comandoLists(const vector<string> &args);

void comandoDels(const vector<string> &args);

std::string converterTipoCaravana(char tipo);

#endif //SIMDESERTO_UTILS_H
