//
// Created by Tiago on 02/12/2024.
//

#include "../include/Buffer.h"

// Construtor
Buffer::Buffer(int linhas, int colunas) : linhas(linhas), colunas(colunas), linhaCursor(0), colunaCursor(0) {
    data = new char[linhas * colunas];
    clear();
}

// Destrutor: libera a memória alocada
Buffer::~Buffer() {
    delete[] data;
}

void Buffer::setDimensoes(int novasLinhas, int novasColunas) {
    linhas = novasLinhas;
    colunas = novasColunas;
    resizeBuffer();
}




// Esvaziar o buffer
void Buffer::clear() {
    memset(data, '.', linhas * colunas);
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
        std::cout << '\n';
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

// Escrever um caracter
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

char Buffer::getChar(int linha, int coluna) {
    int indice = calcularIndice(linha, coluna);
    if (indice == -1) return '.';
    return data[indice];
}


void Buffer::resizeBuffer() {
    char* novoData = new char[linhas * colunas];
    memset(novoData, '.', linhas * colunas);

    // Copia os dados antigos para o novo array
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            novoData[(i * colunas) + j] = data[(i * colunas) + j];
        }
    }

    //delete[] data; // Limpar memoria do array antigo
    data = novoData;
}

// Construtor de Cópia para copiar buffer
Buffer::Buffer(const Buffer& copia)
        : linhas(copia.linhas), colunas(copia.colunas), linhaCursor(copia.linhaCursor), colunaCursor(copia.colunaCursor) {
    data = new char[linhas * colunas];
    memcpy(data, copia.data, linhas * colunas);
}

// Construtor de Movimentação
Buffer::Buffer(Buffer&& copia) noexcept
        : linhas(copia.linhas), colunas(copia.colunas), linhaCursor(copia.linhaCursor), colunaCursor(copia.colunaCursor), data(copia.data) {
    copia.data = nullptr;
}