//
// Created by Pedro on 11/3/2024.
//

#include "../include/Deserto.h"


// Construtor: inicializa o mapa com pontos (.)
Deserto::Deserto(const Buffer &bufferInicial) : buffer(bufferInicial), moedas(0) {}

void Deserto::setLinhas(int l) {
    this->linhas = l;
}

void Deserto::setColunas(int c) {
    this->colunas = c;
}


// Lê a config de um ficheiro
bool Deserto::lerFicheiro(const std::string &filename) {
    std::string folder = "../config/";
    std::string path = folder + filename + ".txt";

    std::ifstream file(path);
    if (!file) {
        std::cerr << "Erro ao abrir o ficheiro: " << filename << std::endl;
        return false;
    }

    std::string lixo;
    int nLinhas, nColunas;

    // Ler as primeiras duas linhas com os tamanhos
    file >> lixo >> nLinhas;
    buffer.setLinhas(nLinhas);
    setLinhas(nLinhas);

    file >> lixo >> nColunas;
    buffer.setColunas(nColunas);
    setColunas(nColunas);

    // Ler cada linha do mapa
    std::string line;
    for (int i = 0; i <= nLinhas && std::getline(file, line); ++i) {
        for (int j = 0; j < std::min(nColunas, static_cast<int>(line.size())); ++j) {
            //mapa[calcularIndice(i - 1, j)] = line[j];
            if (!buffer.moveCursor(i - 1, j)) {
                std::cerr << "[ERRO] Cursor fora dos limites ao carregar o mapa\n";
                return false;
            }
            buffer.writeChar(line[j]);
        }

    }
    std::cout << "Mapa carregado:\n";
    buffer.print();
    //mostrarMapa();

    // Ler valores configuráveis
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string chave;
        int valor;

        // Aplicar o valor à configuração correspondente
        if (iss >> chave >> valor) {
            if (chave == "moedas") {
                setMoedas(valor);
                std::cout << "Moedas configuradas: " << valor << std::endl;
            } else if (chave == "instantes_entre_novos_itens") {
                setInstantesEntreNovosItems(valor);
                std::cout << "Instantes entre novos items: " << valor << std::endl;
            } else if (chave == "duração_item") {
                setDuracaoItem(valor);
                std::cout << "Duração do item: " << valor << std::endl;
            } else if (chave == "max_itens") {
                setMaxItens(valor);
                std::cout << "Máximo de itens: " << valor << std::endl;
            } else if (chave == "preço_venda_mercadoria") {
                setPrecoVendaMerc(valor);
                std::cout << "Preço de venda de mercadoria: " << valor << std::endl;
            } else if (chave == "preço_compra_mercadoria") {
                setPrecoCompraMerc(valor);
                std::cout << "Preço de compra de mercadoria: " << valor << std::endl;
            } else if (chave == "preço_caravana") {
                setPrecoCaravana(valor);
                std::cout << "Preço da caravana: " << valor << std::endl;
            } else if (chave == "instantes_entre_novos_barbaros") {
                setInstantesEntreNovosBarbaros(valor);
                std::cout << "Instantes entre novos bárbaros: " << valor << std::endl;
            } else if (chave == "duração_barbaros") {
                setDuracaoBarbaros(valor);
                std::cout << "Duração dos bárbaros: " << valor << std::endl;
            } else {
                std::cerr << "Aviso: Configuração desconhecida '" << chave << "'" << std::endl;
            }
        } else {
            std::cerr << "Erro ao ler linha de configuração: " << line << std::endl;
            return false;
        }
    }
    processarBuffer();
    return true;
}

void Deserto::setTerreno(int linha, int coluna, char terreno) {
    buffer.moveCursor(linha, coluna);
    buffer.writeChar(terreno);
}

void Deserto::setMoedas(int valor) {
    this->moedas = valor;
}

void Deserto::setInstantesEntreNovosItems(int valor) {
    this->instantesEntreNovosItems = valor;
}

void Deserto::setDuracaoItem(int valor) {
    this->duracaoItem = valor;
}

void Deserto::setMaxItens(int valor) {
    this->maxItems = valor;
}

void Deserto::setPrecoVendaMerc(int valor) {
    this->precoVendaMerc = valor;
}

void Deserto::setPrecoCompraMerc(int valor) {
    this->precoCompraMerc = valor;
}

void Deserto::setPrecoCaravana(int valor) {
    this->precoCaravana = valor;
}

void Deserto::setInstantesEntreNovosBarbaros(int valor) {
    this->instantesEntreNovosBarbaros = valor;
}

void Deserto::setDuracaoBarbaros(int valor) {
    this->duracaoBarbaros = valor;
}

int Deserto::getNumCaravanas() const {
    return numCaravanas;
}

int Deserto::getMoedas() const {
    return moedas;
}

int Deserto::getPrecoCaravana() const {
    return precoCaravana;
}

void Deserto::printPrecos() const {
    std::cout << "Comprar mercadoria - " << this->precoCompraMerc << " Moedas\nVender mercadoria - "
              << this->precoVendaMerc << " Moedas" << std::endl;
}

void Deserto::ajustarMoedas(int valor) {
    moedas += valor;
    if (moedas < 0) moedas = 0;
    std::cout << valor << " moedas adicionadas" << std::endl;
}

void Deserto::mostrarMapa() const {
    buffer.print();
}

void Deserto::processarBuffer() {
    for (int i = 0; i < buffer.getLinhas(); ++i) {
        for (int j = 0; j < buffer.getColunas(); ++j) {
            char c = buffer.getChar(i, j);

            if (isalpha(c)) {   // Encontrou Cidade
                adicionaCidade(c, i, j);
            } else if (isdigit(c)) {  // Encontrou Caravana
                adicionaCaravana('c', i, j); //Iniicalmente todas caravanas comerciais
            } else if (c == '+') { // Encontrou Montanha
                montanhas.emplace_back(i, j);
            }
        }
    }
}

// Instanciar cidade e adicionar ao vetor
void Deserto::adicionaCidade(char nome, int l, int c) {
    numCidades++;
    cidades.emplace_back(toupper(nome), l, c);
}

// Instanciar caravana e adicionar ao vetor
void Deserto::adicionaCaravana(char tipo, int l, int c) {
    numCaravanas++;
    switch (toupper(tipo)) {
        case 'C': // Comercio
            caravanas.emplace_back(std::make_unique<CaravanaComercio>(l, c));
            break;
        case 'M': // Militar
            caravanas.emplace_back(std::make_unique<CaravanaMilitar>(l, c));
            break;
        case 'S': // Secreta
            caravanas.emplace_back(std::make_unique<CaravanaSecreta>(l, c));
            break;
        default:
            std::cerr << "[ERRO] Tipo de caravana inválido: " << tipo << std::endl;
            return;
    }
}

void Deserto::printCidades() const {
    std::cout << "Cidades no mapa:" << std::endl;
    for (const auto &cidade: cidades) {
        std::cout << "Cidade: " << cidade.getNome()
                  << " | Posicao: (" << cidade.getLinha() << ", " << cidade.getColuna() << ")" << std::endl;
    }
}

const std::vector<std::unique_ptr<Caravana>> &Deserto::getCaravanas() const {
    return caravanas;
}

const std::vector<Cidade> &Deserto::getCidades() const {
    return cidades;
}

std::vector<Cidade> &Deserto::getCidades() {
    return cidades;
}

const std::vector<std::pair<int, int>> &Deserto::getMontanhas() const {
    return montanhas;
}

void Deserto::printCaravanas() const {
    for (const auto &caravana: caravanas) {
        caravana->detalhes();
    }
}

void Deserto::atualizarBuffer() {
    buffer.clear(); // Estado inicial

    // Adicionar montanhas
    for (const auto& montanha : montanhas) {
        buffer.moveCursor(montanha.first, montanha.second);
        buffer.writeChar('+');
    }

    // Adicionar caravanas
    for (const auto& caravana : caravanas) {
        buffer.moveCursor(caravana->getLinha(), caravana->getColuna());
        buffer.writeChar('0'+caravana->getId());
    }

    // Adicionar cidades
    for (const auto& cidade : cidades) {
        buffer.moveCursor(cidade.getLinha(), cidade.getColuna());
        buffer.writeChar(tolower(cidade.getNome()));
    }
}



//Caravanas

int movimentaCima(const std::unique_ptr<Caravana> &caravana, int maxLinha) {
    if (caravana->getLinha() - 1 >= 0) {
        return caravana->getLinha() - 1;
    } else {
        return maxLinha;
    }
}

int movimentaBaixo(const std::unique_ptr<Caravana> &caravana, int maxLinha) {
    if (caravana->getLinha() + 1 <= maxLinha) {
        return caravana->getLinha() + 1;
    } else {
        return 0;
    }
}

int movimentaEsquerda(const std::unique_ptr<Caravana> &caravana, int maxColuna) {
    if (caravana->getColuna() - 1 >= 0) {
        return caravana->getColuna() - 1;
    } else {
        return maxColuna;
    }
}

int movimentaDireita(const std::unique_ptr<Caravana> &caravana, int maxColuna) {
    if (caravana->getColuna() + 1 <= maxColuna) {
        return caravana->getColuna() + 1;
    } else {
        return 0;
    }
}

void Deserto::moverCaravana(int id, const std::string& movimento) {
    for (const auto &caravana: caravanas) {
        if (caravana->getId() == id) {
            int posLinhaNova = caravana->getLinha(), posColunaNova = caravana->getColuna();
            // Validação de limites
            if (movimento == "C") {
                posLinhaNova = movimentaCima(caravana, linhas - 1);
            } else if (movimento == "B") {
                posLinhaNova = movimentaBaixo(caravana, linhas - 1);
            } else if (movimento == "E") {
                posColunaNova = movimentaEsquerda(caravana, colunas - 1);
            } else if (movimento == "D") {
                posColunaNova = movimentaDireita(caravana, colunas - 1);
            } else if (movimento == "CE") {
                posLinhaNova = movimentaCima(caravana, linhas - 1);
                posColunaNova = movimentaEsquerda(caravana, colunas - 1);
            } else if (movimento == "CD") {
                posLinhaNova = movimentaCima(caravana, linhas - 1);
                posColunaNova = movimentaDireita(caravana, colunas - 1);
            } else if (movimento == "BE") {
                posLinhaNova = movimentaBaixo(caravana, linhas - 1);
                posColunaNova = movimentaEsquerda(caravana, colunas - 1);
            } else if (movimento == "BD") {
                posLinhaNova = movimentaBaixo(caravana, linhas - 1);
                posColunaNova = movimentaDireita(caravana, colunas - 1);
            }

            if (movimentoInvalido(posLinhaNova, posColunaNova)) {
                std::cerr << "[ERRO] Movimento inválido\n";
                return;
            }

            // Move a caravana para a nova posição
            caravana->mover(posLinhaNova, posColunaNova);
            std::cout << "Caravana " << id << " movida para (" << posLinhaNova << ", " << posColunaNova << ")\n";
            return;
        }
    }
    std::cerr << "Erro: Caravana " << id << " nao encontrada\n";
}

bool Deserto::movimentoInvalido(int linha, int coluna) {
    // Verificar se está dentro dos limites
    if (linha < 0 || linha >= buffer.getLinhas() || coluna < 0 || coluna >= buffer.getColunas()) return true;

    // Verificar se posição está ocupada por uma montanha
    if (std::find(montanhas.begin(), montanhas.end(), std::make_pair(linha, coluna)) != montanhas.end()) return true;

    for (const Cidade& cidade : cidades){
        if(cidade.getLinha() == linha && cidade.getColuna() == coluna) return false; // Permitir varias caravanas em cidades
    }

    // Verificar se posição está ocupada por uma caravana
    for (const auto &caravana: caravanas) {
        if (caravana->getLinha() == linha && caravana->getColuna() == coluna) return true;
    }

    return false; // Movimento é válido
}
