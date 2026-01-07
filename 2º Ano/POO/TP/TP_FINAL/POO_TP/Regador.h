#ifndef POO_TP_REGADOR_H
#define POO_TP_REGADOR_H
#include "Ferramenta.h"
#include "Settings.h"
#include "Celula.h"

class Regador : public Ferramenta{
public:
    Regador();

    char getSimbolo() const override {return 'g';}
    std::string getNome() const override { return "Regador"; }

    Ferramenta* clone() const override { return new Regador(*this); }

    bool usa(Celula &c) override;
};


#endif //POO_TP_REGADOR_H
