#include "../include/Utils.h"

using namespace std;

int main() {
    // Set the global locale to UTF-8
    std::locale::global(std::locale(""));

    // Inicializa o deserto
    Deserto desertoInicial(0, 0);

    int fase = 1;
    do {
        std::cout << "\nFase " << fase << std::endl;
        fase = lerComandos(fase, desertoInicial);
    } while (fase);

    return 0;
}