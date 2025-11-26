#ifndef POO_TP_INVENTARIO_H
#define POO_TP_INVENTARIO_H
#include "Ferramenta.h"

class Inventario {
private:
    static const int MAX_Ferramentas = 15;
    Ferramenta *ferramentas[MAX_Ferramentas];
    Ferramenta *naMao;
    int nrFerramentas;
    int procurar(int nrSerie) const;

public:
    Inventario();

    bool adicionar(Ferramenta* f);
    Ferramenta* pegar(int nrSerie);
    bool largar();

    Ferramenta* getNaMao() const { return naMao; }
    int getNrFerramentas() const { return nrFerramentas; }

    const Ferramenta* getFerramenta(int nrSerie) const;
    std::string descricao() const;
};


#endif //POO_TP_INVENTARIO_H
