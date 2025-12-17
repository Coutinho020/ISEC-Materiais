#ifndef POO_TP_ADUBO_H
#define POO_TP_ADUBO_H
#include "Ferramenta.h"
#include "Celula.h"
#include "Settings.h"

class Adubo : public Ferramenta {
public:
    Adubo();

    char getSimbolo() const override { return 'a'; }
    std::string getNome() const override { return "Pacote de Adubo"; }

    void usa(Celula &c) override;
};

#endif //POO_TP_ADUBO_H
