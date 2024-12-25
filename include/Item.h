
class Item {
protected:
    int tempoRestante;
    int linha, coluna;
    int tipo; // 1 - Caixa de Pandora \ 2 - Arca do tesouro \ 3 - Jaula \ 4 - Mina \ 5 - Surpresa
public:
    Item(int linha, int coluna, int tipo, int turnosRestantes);

    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    int getTipo() const { return tipo; }

    bool atualizar();
};