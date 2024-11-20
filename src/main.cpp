#include "../include/Deserto.h"
#include "../include/Barbaro.h"
#include "../include/Caravana.h"
#include "../include/Cidade.h"
#include "../include/Item.h"
#include "../include/Utils.h"

using namespace std;

int main() {
    // Definimos as dimensões do deserto
    int linhas = 10;
    int colunas = 10;

    // Criamos o objeto Deserto
    Deserto deserto(linhas, colunas);

    // Carregamos o mapa a partir de um ficheiro de exemplo
    /*if (!deserto.loadMap("config/default_map.txt")) {
        std::cerr << "Falha ao carregar o mapa." << std::endl;
        return 1;
    }*/

    // Exibimos o mapa carregado
    deserto.displayMap();

    // Modificar 5 posições aleatórias para o tipo de terreno montanha ('+')
    for (int i = 0; i < 5; ++i) {
        int linhaAleatoria = rand() % linhas;
        int colunaAleatoria = rand() % colunas;
        deserto.setTerrain(linhaAleatoria, colunaAleatoria, '+');
    }

    // Exibir o mapa após as modificações
    cout << "\nMapa apos modificar 5 posicoes aleatorias:" << endl;
    deserto.displayMap();

    cout << "Tiagao é massudo" << endl;
    return 0;
}
