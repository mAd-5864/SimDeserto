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
    std::cout << "Mapa carregado\n";

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
                std::cout << "Duracao do item: " << valor << std::endl;
            } else if (chave == "max_itens") {
                setMaxItens(valor);
                std::cout << "Maximo de itens: " << valor << std::endl;
            } else if (chave == "preço_venda_mercadoria") {
                setPrecoVendaMerc(valor);
                std::cout << "Preco de venda de mercadoria: " << valor << std::endl;
            } else if (chave == "preço_compra_mercadoria") {
                setPrecoCompraMerc(valor);
                std::cout << "Preco de compra de mercadoria: " << valor << std::endl;
            } else if (chave == "preço_caravana") {
                setPrecoCaravana(valor);
                std::cout << "Preco da caravana: " << valor << std::endl;
            } else if (chave == "instantes_entre_novos_barbaros") {
                setInstantesEntreNovosBarbaros(valor);
                std::cout << "Instantes entre novos barbaros: " << valor << std::endl;
            } else if (chave == "duração_barbaros") {
                setDuracaoBarbaros(valor);
                std::cout << "Duracao dos barbaros: " << valor << std::endl;
            } else {
                std::cerr << "Aviso: Configuracao desconhecida '" << chave << "'" << std::endl;
            }
        } else {
            std::cerr << "Erro ao ler linha de configuracao: " << line << std::endl;
            return false;
        }
    }
    processarBuffer();
    mostrarMapa();
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

int Deserto::getPrecoCompraMerc() const {
    return precoCompraMerc;
}

int Deserto::getPrecoVendaMerc() const {
    return precoVendaMerc;
}

void Deserto::ajustarMoedas(int valor) {
    moedas += valor;
    if (moedas < 0) moedas = 0;
    if (valor >= 0)
        std::cout << valor << " moedas adicionadas" << std::endl;
    else
        std::cout << abs(valor) << " moedas removidas" << std::endl;
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
                int chance = rand() % 3;
                if (chance < 2) {  // 66% de chance para militar
                    adicionaCaravana('m', i, j);
                } else {           // 33% de chance para comercial
                    adicionaCaravana('c', i, j);
                }
            } else if (c == '+') { // Encontrou Montanha
                montanhas.emplace_back(i, j);
            } else if (c == '!') { // Encontrou Barbaro
                adicionaBarbaro(i, j);
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
            std::cerr << "[ERRO] Tipo de caravana invalido: " << tipo << std::endl;
            return;
    }
}

void Deserto::adicionaBarbaro(int linha, int coluna){
    barbaros.emplace_back(linha, coluna, 40, duracaoBarbaros);
}

void Deserto::adicionaItem(int linha, int coluna, int tipo) {
    // adicionar tipo e duracao ao construtor
    itens.emplace_back(linha, coluna, tipo, duracaoItem);
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

const std::vector<Barbaro> &Deserto::getBarbaros() {
    return barbaros;
}

void Deserto::printCaravanas() const {
    for (const auto &caravana: caravanas) {
        caravana->detalhes();
    }
}

void Deserto::atualizarBuffer() {
    buffer.clear(); // Estado inicial

    // Adicionar barbaros
    for (const auto &barbaro: barbaros) {
        buffer.moveCursor(barbaro.getLinha(), barbaro.getColuna());
        buffer.writeChar('!');
    }

    // Adicionar montanhas
    for (const auto &montanha: montanhas) {
        buffer.moveCursor(montanha.first, montanha.second);
        buffer.writeChar('+');
    }

    // Adicionar items
    for (const auto &item: itens) {
        buffer.moveCursor(item.getLinha(), item.getColuna());
        buffer.writeChar('?');
    }

    // Adicionar caravanas
    for (const auto &caravana: caravanas) {
        buffer.moveCursor(caravana->getLinha(), caravana->getColuna());
        buffer.writeChar('0' + caravana->getId());
    }

    // Adicionar cidades
    for (const auto &cidade: cidades) {
        buffer.moveCursor(cidade.getLinha(), cidade.getColuna());
        buffer.writeChar(cidade.getNome());
    }
}

//Caravanas

void Deserto::atualizarCaravanas() {
    for (auto it = caravanas.begin(); it != caravanas.end();) {
        auto& caravana = *it;
        caravana->atualizarTurno(); // Chama o método específico de cada tipo

        if (caravana->estaNaCidade(cidades)){
            caravana->reabasteceAgua();
            caravana->setMoveType(0);
        }

        if (caravana->getTipoMovimentacao() == 1) {
            // Caravana militar procura items??
            std::pair<int, int> coords = procuraItem(caravana->getLinha(), caravana->getColuna());
            if (!movimentoInvalido(coords.first, coords.second)) {
                caravana->mover(coords.first, coords.second);
            } else {
                coords = caravana->autoMove(caravanas, barbaros);
                if (!movimentoInvalido(coords.first, coords.second))
                    caravana->mover(coords.first, coords.second);
            }
            if (caravana->getTipo() == 'S') {
                std::cout<<"entrou 1\n";
                // Cast caravana para CaravanaSecreta
                auto* caravanaSecreta = dynamic_cast<CaravanaSecreta*>(caravana.get());
                std::cout<<"entrou 2\n";
                if (caravanaSecreta) {
                    std::cout<<"entrou 3\n";
                    if (!caravanaSecreta->infiltrarBarbaros(barbaros)) {
                        std::cout << "Caravana infiltrada " << caravana->getId() << " foi descoberta pelos barbaros e foi destruida\n";
                        it = caravanas.erase(it);
                    }
                    std::cout<<"entrou 4\n";
                }
            }
            ++it;
        } else if (caravana->getTipoMovimentacao() == 2) {
            if (caravana->getInstantes()) {
                std::pair<int, int> coords = caravana->moveMorrer();
                if (!movimentoInvalido(coords.first, coords.second))
                    caravana->mover(coords.first, coords.second);
                ++it;
            } else {
                std::cout << "Caravana " << caravana->getId() << " ficou sem tripulantes e foi destruida\n";
                it = caravanas.erase(it);
            }
        } else {
            ++it;
        }
    }
}


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

void Deserto::moverCaravana(int id, const std::string &movimento) {
    for (const auto &caravana: caravanas) {
        if (caravana->getId() == id) {
            if (caravana->getTipoMovimentacao()){
                std::cout<<"Caravana "<< caravana->getId()<< " em movimento automatico\n";
                return;
            }
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
                std::cerr << "[ERRO] Movimento invalido\n";
                return;
            }

            // Move a caravana para a nova posição
            caravana->mover(posLinhaNova, posColunaNova);
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

    for (const Cidade &cidade: cidades) {
        if (cidade.getLinha() == linha && cidade.getColuna() == coluna)
            return false; // Permitir varias caravanas em cidades
    }

    // Verificar se posição está ocupada por uma caravana
    for (const auto &caravana: caravanas) {
        if (caravana->getLinha() == linha && caravana->getColuna() == coluna) return true;
    }

    // Verificar se posição está ocupada por barbaros
    for (const Barbaro &barbaro: barbaros) {
        if (barbaro.getLinha() == linha && barbaro.getColuna() == coluna) return true;
    }

    return false; // Movimento é válido
}

bool Deserto::saveBuffer(const std::string &nome) {
    if (bufferSaves.find(nome) != bufferSaves.end()) {
        std::cerr << "[ERRO] Ja existe uma copia com o nome '" << nome << "'\n";
        return false;
    }
    bufferSaves.insert(std::make_pair(nome, buffer)); // Faz uma cópia do buffer atual
    std::cout << "Copia guardada como '" << nome << "'\n";
    return true;
}

bool Deserto::loadBuffer(const std::string &nome) {
    auto it = bufferSaves.find(nome);
    if (it == bufferSaves.end()) {
        std::cerr << "[ERRO] Nao existe nenhuma copia com o nome '" << nome << "'\n";
        return false;
    }

    Buffer copia = it->second;
    std::cout << "-----Buffer " << nome << "-----\n";
    copia.print();
    return true;
}

void Deserto::listBuffer() const {
    if (bufferSaves.empty()) {
        std::cout << "A lista de saves esta vazia\n";
        return;
    }

    std::cout << "Saves disponiveis:\n";
    for (const auto &save: bufferSaves) {
        std::cout << "\t> " << save.first << std::endl;
    }
}

bool Deserto::apagarBuffer(const std::string &nome) {
    if (bufferSaves.erase(nome)) {
        std::cout << "Copia '" << nome << "' apagada com sucesso\n";
        return true;
    } else {
        std::cerr << "[ERRO] Nao existe uma copia com o nome '" << nome << "'\n";
        return false;
    }
}

void Deserto::atualizarBarbaros() {
    for (auto barbaro = barbaros.begin(); barbaro != barbaros.end();) {
        if (!barbaro->atualizar()) {
            barbaro = barbaros.erase(barbaro); // Remove barbaro do vetor
        } else ++barbaro;
    }

    // Adicionar novo bárbaro de x em x instantes
    if (instanteAtual % instantesEntreNovosBarbaros == 0) {
        int linha = rand() % linhas;
        int coluna = rand() % colunas;

        // Verificar se a posição é válida antes de adicionar
        while (!verificarMoveAleatorio(linha, coluna)) {
            linha = rand() % linhas;
            coluna = rand() % colunas;
        }

        adicionaBarbaro(linha, coluna);
    }
}

void Deserto::movimentarBarbaros() {
    for (auto &barbaro: barbaros) {
        Caravana *inimigo = nullptr;
        int distanciaMin = 9, distancia;

        // Verificar se existe uma caravana próxima (distância <= 8)
        for (const auto &caravana: caravanas) {
                //caravana não é perseguida se: estiver numa cidade, estiver sem tripulantes, for caravana secreta
            if (!caravana->estaNaCidade(cidades) && caravana->getTripulantes() && caravana->getTipo()!='S') {
                distancia = abs(barbaro.getLinha() - caravana->getLinha()) +
                            abs(barbaro.getColuna() - caravana->getColuna());
                if (distancia <= 8) {
                    if (distancia < distanciaMin) {
                        distanciaMin = distancia;
                        inimigo = caravana.get();
                    }
                }
            }
        }

        // Se encontrar uma caravana próxima, persegue-a
        if (inimigo) {
            //std::cout << "barbaro "<< barbaro.getId()<<" em perseguicao da caravana " << inimigo->getId() << "\n";
            if (perseguirCaravana(barbaro, inimigo->getLinha(), inimigo->getColuna()))
                combates.emplace_back(inimigo->getId(), barbaro.getId());
        } else {
            std::pair coords = procuraItem(barbaro.getLinha(), barbaro.getColuna());
            if (movimentoInvalido(coords.first, coords.second)){
                barbaro.move(coords.first, coords.second);
                return;
            }
            // Gerar valores aleatórios para movimento (-1, 0, +1)
            int novaLinha = barbaro.getLinha() + (rand() % 3 - 1);
            int novaColuna = barbaro.getColuna() + (rand() % 3 - 1);
            if (verificarMoveAleatorio(novaLinha, novaColuna))
                barbaro.move(novaLinha, novaColuna);
        }
    }
}

bool Deserto::verificarMoveAleatorio(int &novaLinha, int &novaColuna) {
    if (novaLinha == linhas) novaLinha = 0;
    if (novaLinha < 0) novaLinha = linhas - 1;
    if (novaColuna == colunas) novaColuna = 0;
    if (novaColuna < 0) novaColuna = colunas - 1;

    // Verificar se posição está ocupada por uma caravana
    for (const Cidade &cidade: cidades) {
        if (cidade.getLinha() == novaLinha && cidade.getColuna() == novaColuna)
            return false;
    }

    // Verificar se posição está ocupada por uma montanha
    if (std::find(montanhas.begin(), montanhas.end(), std::make_pair(novaLinha, novaColuna)) != montanhas.end())
        return false;

    // Verificar se posição está ocupada por uma caravana
    for (const auto &caravana: caravanas) {
        if (caravana->getLinha() == novaLinha && caravana->getColuna() == novaColuna) return false;
    }

    // Verificar se posição está ocupada por barbaros
    for (const Barbaro &barbaro: barbaros) {
        if (barbaro.getLinha() == novaLinha && barbaro.getColuna() == novaColuna) return false;
    }
    return true;
}

bool Deserto::perseguirCaravana(Barbaro &barbaro, int destinoLinha, int destinoColuna) {
    int novaLinha = barbaro.getLinha();
    int novaColuna = barbaro.getColuna();
    int distancia = abs(novaLinha - destinoLinha) +
                    abs(novaColuna - destinoColuna);

    // Determinar direção para a coluna
    if (distancia > 1) {
        if (novaColuna < destinoColuna) {
            novaColuna++;
        } else if (novaColuna > destinoColuna) {
            novaColuna--;
        }
        distancia = abs(novaLinha - destinoLinha) +
                    abs(novaColuna - destinoColuna);
    }

    if (distancia > 1) {
        // Determinar direção para a linha
        if (novaLinha < destinoLinha) {
            novaLinha++;
        } else if (novaLinha > destinoLinha) {
            novaLinha--;
        }
    }

    distancia = abs(novaLinha - destinoLinha) +
                abs(novaColuna - destinoColuna);

    if (verificarMoveAleatorio(novaLinha,novaColuna)){
        barbaro.move(novaLinha,novaColuna);
        if (distancia <= 1) {
            return true; // Entra em combate!!
        }
    }else { // Caso nao consiga perseguir move-se aleatoriamente
        // Gerar valores aleatórios para movimento (-1, 0, +1)
        novaLinha = barbaro.getLinha() + (rand() % 3 - 1);
        novaColuna = barbaro.getColuna() + (rand() % 3 - 1);
        if (verificarMoveAleatorio(novaLinha, novaColuna))
            barbaro.move(novaLinha, novaColuna);
    }
    return false;
}

void Deserto::processarCombates() {
    if (!combates.empty()) {
        std::cout << "Combates a decorrer:" << std::endl;
        for (const auto &comabte: combates) {
            std::cout << comabte.first << " vs " << comabte.second << std::endl;
            // TODO iniciar o combate
        }
        combates.clear();
    }
}

void Deserto::atualizarItems(){
    for (auto item = itens.begin(); item != itens.end();) {
        bool itemProcessed = false;

        // Check interaction with caravanas
        for (auto& caravana : caravanas) {
            if (caravana->getLinha() == item->getLinha() && caravana->getColuna() == item->getColuna()) {
                if (processarItem(*caravana, item->getTipo(), caravana->getMaxTripulantes())){
                    caravana = nullptr;
                    caravanas.erase(std::remove(caravanas.begin(), caravanas.end(), nullptr), caravanas.end());
                }
                item = itens.erase(item);
                itemProcessed = true;
                break;
            }
        }
        if (itemProcessed) continue;

        // Check interaction with barbaros
        for (auto& barbaro : barbaros) {
            if (barbaro.getLinha() == item->getLinha() && barbaro.getColuna() == item->getColuna()) {
                if(processarItem(barbaro, item->getTipo(), 40)){
                    barbaros.erase(
                            std::remove_if(
                                    barbaros.begin(),
                                    barbaros.end(),
                                    [&barbaro](const Barbaro& b) { return b.getId() == barbaro.getId(); } // Encontrar ID
                            ),
                            barbaros.end()
                    );
                }
                item = itens.erase(item);
                itemProcessed = true;
                break;
            }
        }
        if (itemProcessed) continue;

        // Caso acabe o tempo de vida do item
        if (!item->atualizar()) {
            item = itens.erase(item);
        } else ++item;
    }

    if(numeroItens <= maxItems && instanteAtual%instantesEntreNovosItems==0) {
        // Gerar novo item
        int linhaAleatoria, colunaAleatoria, tipo;
        do {
            // Gerar valores aleatórios
            linhaAleatoria = (rand() % linhas);
            colunaAleatoria = (rand() % colunas);
            tipo = (rand() % 5+1);
        } while (!verificarMoveAleatorio(linhaAleatoria, colunaAleatoria));

        adicionaItem(linhaAleatoria, colunaAleatoria, tipo);
    }
}

std::pair<int, int> Deserto::procuraItem(int linha, int coluna){
    // Procurar items a 4 posicoes de distancia
    int alvo = 0, linhaItem, colunaItem;
    int distanciaMin = 999, distancia;
    for (const auto &item : itens) {
        distancia = abs(item.getLinha() - linha) +
                    abs(item.getColuna() - coluna);

        if (distancia<=4) {
            if (distancia < distanciaMin) {
                distanciaMin = distancia;
                alvo = item.getTipo();
                linhaItem = item.getLinha();
                colunaItem = item.getColuna();
            }
        }
    }
    // Caso encontre um item
    if (alvo) {
        int novaLinha = linha;
        int novaColuna = coluna;

        // Mover em direcao ao Item
        if (novaColuna < colunaItem) {
            novaColuna++;
        } else if (novaColuna > colunaItem) {
            novaColuna--;
        }
        if (novaLinha < linhaItem) {
            novaLinha++;
        } else if (novaLinha > linhaItem) {
            novaLinha--;
        }
        return std::make_pair(novaLinha, novaColuna);
    }
    return std::make_pair(linha, coluna);
}

template <typename Entity>
bool Deserto::processarItem(Entity& entity, int itemTipo, int maxTripulantes) {
    switch (itemTipo) {
        case 1: { // Caixa de Pandora
            int tripulantesPerdidos = floor(entity.getTripulantes() * 0.2);
            std::cout << entity.getId() << " abriu uma Caixa de Pandora e perdeu "
                      << tripulantesPerdidos << " tripulantes\n";
            entity.addTripulantes(-tripulantesPerdidos);
            break;
        }
        case 2: { // Arca do Tesouro
            std::cout << entity.getId() << " abriu uma Arca do Tesouro\n";
            ajustarMoedas(moedas * 0.1); // Assuming `ajustarMoedas` is defined elsewhere
            break;
        }
        case 3: { // Jaula com Prisioneiros
            int maxPrisioneiros = maxTripulantes - entity.getTripulantes();
            if (maxPrisioneiros){
            int nPrisioneiros = rand() % (maxTripulantes - entity.getTripulantes());
            std::cout << entity.getId() << " encontrou uma jaula com "
                      << nPrisioneiros << " prisioneiros\n";
            entity.addTripulantes(nPrisioneiros);
                break;
            }
            std::cout << entity.getId() << " encontrou uma jaula com prisioneiros mas tem o maximo de tripulantes\n";
            break;
        }
        case 4: { // Mina
            std::cout << entity.getId() << " explodiu numa mina da WW2\n";
            return true;
        }
    }
    return false;
}

int Deserto::criaTempestade(int linha, int coluna, int raio) {
    int estaDentro; // 0 - esta dentro \\ 1 - esta fora
    int probabilidade;
    if(linha < 0 || coluna < 0 || raio < 0)
        return 1;

    tempestades.emplace_back(linha,coluna,raio);

    for (const auto &caravana: caravanas){

        if ((estaDentro = tempestades.back().verificaDentro(caravana->getLinha(), caravana->getColuna())) == 0){
            probabilidade = (std::rand() % (100)) + 1;
            if (caravana->getTipo() == 'C'){
                if( ( caravana->getCarga() * 100 / caravana->getMaxCarga() ) > 50 ){
                    if (probabilidade > 50){
                        //eleminar Caravana
                    }
                }else{
                    if (probabilidade < 25){
                        //eleminar Caravana
                    }
                }
            }else if (caravana->getTipo() == 'M'){

            } else if (caravana->getTipo() == 'S'){

            }
        }
    }
}