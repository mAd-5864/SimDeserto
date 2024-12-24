//
// Created by Pedro on 11/3/2024.
//

#include "../include/Item.h"

//Construtor da class
Item::Item(int lin, int col, int tipo, int turnosRestantes) : linha(lin), coluna(col), tipo(tipo), tempoRestante(turnosRestantes){}

bool Item::atualizar(){
    if (tempoRestante == 0) return false;
    tempoRestante--;
    return true;
}