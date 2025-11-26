#ifndef POO_TP_JARDINEIRO_H
#define POO_TP_JARDINEIRO_H
#include "Posicao.h"
#include "Inventario.h"

class Jardim;

class Jardineiro {
    Inventario inventario;
    Posicao pos;
    bool dentroDoJardim;

public:
    Jardineiro();

    void entra(const Posicao &p);
    bool sai();
    bool estaNoJardim() const {return dentroDoJardim;}

    Posicao getPos() const {return pos;}

    bool move(char dir, const Jardim &j);

    Inventario &getInventario();

    bool PegarFerramenta(int nrSerie);
    bool largarFerramenta();
};


#endif //POO_TP_JARDINEIRO_H
