//
// Created by Pedro on 11/3/2024.
//

#ifndef SIMDESERTO_ITEM_H
#define SIMDESERTO_ITEM_H


#include "Utils.h"

class Item {
protected:
    int tempoRestante;
    Position pos;
    string tipo;
public:
    ~Item();
};


#endif //SIMDESERTO_ITEM_H
