//
// Created by Tiago on 02/12/2024.
//

#ifndef SIMDESERTO_BUFFER_H
#define SIMDESERTO_BUFFER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <map>
#include <locale>
#include <cstring>
#include <ostream>

class Buffer {
private:
    char* data;
    int linhas, colunas;
    int linhaCursor, colunaCursor;

    // Calcula o índice no vetor com base na linha e coluna
    int calcularIndice(int linha, int coluna) const;

    // Redimensiona o buffer
    void resizeBuffer();

public:
    // Construtor e destrutor
    Buffer(int linhas, int colunas);
    ~Buffer();

    // Definir tamanho do buffer
    void setDimensoes(int nLinhas, int nColunas);

    // Esvaziar o buffer
    void clear();

    // Imprimir o buffer na consola
    void print() const;

    // Mover o cursor
    bool moveCursor(int r, int c);

    // Escrever um caracter
    void writeChar(char c);

    // Devolve char na posicao (l,c)
    char getChar(int linha, int ccoluna);
};

#endif //SIMDESERTO_BUFFER_H
