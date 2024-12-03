//
// Created by Tiago on 02/12/2024.
//

#ifndef SIMDESERTO_BUFFER_H
#define SIMDESERTO_BUFFER_H

#include "Utils.h"

class Buffer {
    char* data;                     // Área de armazenamento do buffer
    int linhas, colunas;            // Dimensões do buffer
    int linhaCursor, colunaCursor;  // Posição atual do cursor

public:
    // Construtor e destrutor
    Buffer(int r, int c);
    ~Buffer();

    // Esvaziar o buffer
    void clear();

    // Imprimir o buffer na consola
    void print() const;

    // Mover o cursor
    void moveCursor(int r, int c);

    // Escrever um caracter
    void writeChar(char c);

    // Escrever uma string
    void writeString(const char* str);

    // Sobrecarga do operador <<
    Buffer& operator<<(const char* str);
    Buffer& operator<<(char c);
    Buffer& operator<<(int num);

    char *getData();
};

#endif //SIMDESERTO_BUFFER_H
