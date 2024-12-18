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
#include <ostream>

class Buffer {
private:
    std::vector<char> data;
    int linhas, colunas;
    int linhaCursor, colunaCursor;
    void resizeBuffer();

public:
    // Construtor e destrutor
    Buffer(int linhas, int colunas);
    //~Buffer();
    void setLinhas(int l);
    void setColunas(int c);

    int getLinhas(){
        return this->linhas;
    }
    int getColunas(){
        return this->colunas;
    }

    // Esvaziar o buffer
    void clear();

    // Calcula o índice no vetor com base na linha e coluna
    int calcularIndice(int linha, int coluna) const;

    // Imprimir o buffer na consola
    void print() const;

    // Mover o cursor
    bool moveCursor(int r, int c);

    // Escrever um caracter
    void writeChar(char c);

    // Escrever uma string
    void writeString(const char* str);

    // Devolve char na posicao (l,c)
    char getChar(int linha, int ccoluna);

    // Sobrecarga do operador <<
    Buffer& operator<<(const char* str);
    Buffer& operator<<(char c);
    Buffer& operator<<(int num);

    // Debugging helper
    void debugState() const {
        std::cout << "Buffer: " << linhas << "x" << colunas << " | Cursor: (" << linhaCursor << ", " << colunaCursor << ")\n";
    }
};

#endif //SIMDESERTO_BUFFER_H
