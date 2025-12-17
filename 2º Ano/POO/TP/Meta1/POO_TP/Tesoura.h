#ifndef POO_TP_TESOURA_H
#define POO_TP_TESOURA_H
#include "Ferramenta.h"
#include "Celula.h"

class Tesoura : public Ferramenta {
public:

    Tesoura();

    char getSimbolo() const override { return 't'; }
    std::string getNome() const override { return "Tesoura de Poda"; }

    void usa(Celula &c) override;
};

#endif //POO_TP_TESOURA_H
