#ifndef POO_TP_TESOURA_H
#define POO_TP_TESOURA_H
#include "Ferramenta.h"
#include "Celula.h"
#include "Planta.h"

class Tesoura : public Ferramenta {
public:

    Tesoura();

    char getSimbolo() const override { return 't'; }
    std::string getNome() const override { return "Tesoura de Poda"; }

    Ferramenta* clone() const override { return new Tesoura(*this); }

    bool usa(Celula &c) override;
};

#endif //POO_TP_TESOURA_H
