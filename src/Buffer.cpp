//
// Created by Tiago on 02/12/2024.
//

#include "../include/Buffer.h"


void Buffer::setLinhas(int l) {
        linhas = l;
        resizeBuffer();
}

void Buffer::setColunas(int c) {
    colunas = c;
    resizeBuffer();
}

// Construtor
Buffer::Buffer(int r, int c) : linhas(r), colunas(c), linhaCursor(0), colunaCursor(0) {
    data.resize(linhas * colunas, ' '); // Inicializar com espacos
}

// Destrutor
//Buffer::~Buffer() {
//    delete[] data; // Libera memória
//}

// Esvaziar o buffer
void Buffer::clear() {
    std::fill(data.begin(), data.end(), ' ');
    linhaCursor = colunaCursor = 0; // Reset cursor
}

// Calcula o índice no vetor com base na linha e coluna
int Buffer::calcularIndice(int linha, int coluna) const {
    return (linha * colunas) + coluna;
}

// Imprimir o buffer na consola
void Buffer::print() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << data[calcularIndice(i, j)];
        }
        std::cout << std::endl;
    }
}

// Mover o cursor
bool Buffer::moveCursor(int r, int c) {
    if (r >= 0 && r < linhas && c >= 0 && c < colunas) {
        linhaCursor = r;
        colunaCursor = c;
        return true;
    }
    std::cerr << "[ERRO] Cursor fora dos limites: (" << r << ", " << c << ")\n";
    return false;
}

// Escrever um caractere
void Buffer::writeChar(char c) {
    if (linhaCursor >= 0 && linhaCursor <= linhas && colunaCursor >= 0 && colunaCursor < colunas) {
        data[calcularIndice(linhaCursor, colunaCursor)] = c;

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

void Buffer::resizeBuffer() {
    data.clear();
    data.resize(linhas * colunas, ' ');
    linhaCursor = colunaCursor = 0;
}
