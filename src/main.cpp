#include "../include/Utils.h"

using namespace std;

int main() {
    // Set the global locale to UTF-8
    std::locale::global(std::locale(""));
    srand(static_cast<unsigned int>(time(nullptr))); // Seed com a hora atual

    // Inicializa o deserto
    Deserto* desertoInicial = nullptr;

    int fase = 1;
    do {
        if (fase==1) {
            delete desertoInicial;
            desertoInicial = new Deserto(Buffer(0, 0));
            Caravana::resetID();
            std::cout << "\nFase " << fase<< "\n";
        }
        if (fase==2){
            //system("Color E4");
            std::cout << "\nFase " << fase<< " | Instante "<< desertoInicial->getInstante()<<" - Moedas: "<< desertoInicial->getMoedas()<< "   Caravanas: "<< desertoInicial->getNumCaravanas()<<"\n";
        }
        fase = lerComandos(fase, *desertoInicial);
    } while (fase!=0);

    return 0;
}