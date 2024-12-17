#include "../include/Utils.h"

using namespace std;

int main() {
    // Set the global locale to UTF-8
    std::locale::global(std::locale(""));

    // Inicializa o deserto
    Deserto desertoInicial(Buffer(0, 0));

    int fase = 1;
    do {
        std::cout << "\nFase " << fase << std::endl;
        fase = lerComandos(fase, desertoInicial);
        std::cout << "saiu do lerComandos com: " << fase << std::endl;
    } while (fase!=0);

    return 0;
}
/*
int main() {
    Buffer buffer(10, 30); // Buffer de 10 linhas por 30 colunas

    buffer.moveCursor(2, 5);
    buffer.writeString("Olá, Mundo!");

    buffer.moveCursor(4, 10);
    buffer.writeString("Simulador iniciado...");

    buffer.print(); // Mostra o conteúdo na consola

    return 0;
}
*/