#include "../include/Deserto.h"
#include "../include/Barbaro.h"
#include "../include/Caravana.h"
#include "../include/Cidade.h"
#include "../include/Item.h"
#include "../include/Utils.h"

using namespace std;

int main() {
    // Set the global locale to UTF-8
    std::locale::global(std::locale(""));

    int fase = 1;
    while (1) {
        std::cout << "\nFase " << fase << std::endl;
        fase = lerComandos(fase);
    }

    return 0;
}
