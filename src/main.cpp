#include "../include/Deserto.h"
#include "../include/Barbaro.h"
#include "../include/Caravana.h"
#include "../include/Cidade.h"
#include "../include/Item.h"
#include "../include/Utils.h"

using namespace std;

int main() {
    int fase = 1;
    while (1){

    if (lerComandos(fase) == 0) fase = 2;
    }

    return 0;
}
