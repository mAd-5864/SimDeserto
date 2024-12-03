//
// Created by Tiago on 02/12/2024.
//

#include "../include/Buffer.h"


// Construtor
Buffer::Buffer(int r, int c) : linhas(r), colunas(c), linhaCursor(0), colunaCursor(0) {
    data = new char[linhas * colunas]; // Aloca espaço para a "matriz" linear
    clear();                           // Inicializa o buffer vazio
}

// Destrutor
Buffer::~Buffer() {
    delete[] data; // Libera memória
}

// Esvaziar o buffer
void Buffer::clear() {
    std::fill(data, data + linhas * colunas, ' '); // Preenche o buffer com espaços
}

// Imprimir o buffer na consola
void Buffer::print() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << data[i * colunas + j];
        }
        std::cout << std::endl;
    }
}

// Mover o cursor
void Buffer::moveCursor(int r, int c) {
    if (r >= 0 && r < linhas && c >= 0 && c < colunas) {
        linhaCursor = r;
        colunaCursor = c;
    }
}

// Escrever um caractere
void Buffer::writeChar(char c) {
    if (linhaCursor >= 0 && linhaCursor < linhas && colunaCursor >= 0 && colunaCursor < colunas) {
        data[linhaCursor * colunas + colunaCursor] = c;

        // Move o cursor para a próxima posição
        if (++colunaCursor >= colunas) {
            colunaCursor = 0;
            ++linhaCursor;
        }
    }
}

// Escrever uma string
void Buffer::writeString(const char* str) {
    while (*str) {
        writeChar(*str++);
    }
}

// Sobrecarga do operador <<
Buffer& Buffer::operator<<(const char* str) {
    writeString(str);
    return *this;
}

Buffer& Buffer::operator<<(char c) {
    writeChar(c);
    return *this;
}

Buffer& Buffer::operator<<(int num) {
    writeString(std::to_string(num).c_str());
    return *this;
}

char *Buffer::getData() {
    return data;
}
