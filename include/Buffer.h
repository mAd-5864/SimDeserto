//
// Created by Tiago on 02/12/2024.
//

#ifndef SIMDESERTO_BUFFER_H
#define SIMDESERTO_BUFFER_H


#include <iostream>

class Buffer {
    char* data;          // Ponteiro para armazenar os caracteres.
    int rows, cols;      // Dimensões do buffer.
    int cursorRow, cursorCol; // Posição atual do cursor.

public:
    // Construtor
    Buffer(int r, int c) : rows(r), cols(c), cursorRow(0), cursorCol(0) {
        data = new char[rows * cols]; // Aloca espaço para a "matriz" linear.
        clear(); // Inicializa o buffer vazio.
    }

    // Destrutor
    ~Buffer() {
        delete[] data; // Libera memória.
    }

    // Esvaziar o buffer
    void clear() {
        std::fill(data, data + rows * cols, ' ');
    }

    // Imprimir o buffer na consola
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i * cols + j];
            }
            std::cout << std::endl;
        }
    }

    // Mover o cursor
    void moveCursor(int r, int c) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            cursorRow = r;
            cursorCol = c;
        }
    }

    // Escrever um caractere
    void writeChar(char c) {
        if (cursorRow >= 0 && cursorRow < rows && cursorCol >= 0 && cursorCol < cols) {
            data[cursorRow * cols + cursorCol] = c;
            if (++cursorCol >= cols) { // Move para próxima linha se necessário.
                cursorCol = 0;
                ++cursorRow;
            }
        }
    }

    // Escrever uma string
    void writeString(const char* str) {
        while (*str) {
            writeChar(*str++);
        }
    }

    // Sobrecarga do operador <<
    Buffer& operator<<(const char* str) {
        writeString(str);
        return *this;
    }

    Buffer& operator<<(char c) {
        writeChar(c);
        return *this;
    }

    Buffer& operator<<(int num) {
        writeString(std::to_string(num).c_str());
        return *this;
    }
};



#endif //SIMDESERTO_BUFFER_H
