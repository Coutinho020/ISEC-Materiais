#ifndef POO_TP_SUPLEMENTONATURAL_H
#define POO_TP_SUPLEMENTONATURAL_H
#include "Ferramenta.h"
#include "Settings.h"
#include "Celula.h"
#include "Planta.h"

class SuplementoNatural : public Ferramenta {
public:

    SuplementoNatural();

    char getSimbolo() const override { return 'z'; }
    std::string getNome() const override { return "Suplemento Natural"; }

    Ferramenta* clone() const override { return new SuplementoNatural(*this); }

    bool usa(Celula &c) override;

    static const int capacidade = 75;
    static const int dose_planta = 15;
};


#endif //POO_TP_SUPLEMENTONATURAL_H
