#ifndef POO_TP_JARDIM_H
#define POO_TP_JARDIM_H
#include <iostream>
#include "Celula.h"
#include "Jardineiro.h"
#include "Planta.h"
#include "Ferramenta.h"

const int MAX_LINS = 26;
const int MAX_COLS = 26;

class Jardim {

    int lins;
    int cols;
    Celula* celulas;
    Jardineiro jardineiro;

public:
    Jardim();
    ~Jardim();

    bool inicializa(int l, int c);

    int index(int l, int c) const;

    Celula& aceder(int l, int c);
    const Celula& aceder(int l, int c) const;

    Jardineiro& getJardineiro() { return jardineiro; }
    const Jardineiro& getJardineiro() const { return jardineiro; }

    int getLinhas() const{return lins;}
    int getCols() const {return cols;}

    void print() const;

    bool PosicaoValida(int l, int c) const;

    bool adicionarPlanta(const Posicao& p, char tipo);
    bool removerPlanta(const Posicao& p);
};


#endif //POO_TP_JARDIM_H
