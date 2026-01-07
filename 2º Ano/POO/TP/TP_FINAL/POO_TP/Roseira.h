#ifndef POO_TP_ROSEIRA_H
#define POO_TP_ROSEIRA_H
#include "Planta.h"
#include "Settings.h"
#include "Celula.h"

class Roseira : public Planta {
public:

    Roseira();

    char getSimbolo() const override { return 'r';}
    std::string getNome() const override {return "Roseira";}
    std::string getBeleza() const override {return "bonita";}

    Planta* clone() const override { return new Roseira(*this); }

    [[nodiscard]] Planta *multiplicar() override;
    void processaInstante(Celula &c) override;
};

#endif //POO_TP_ROSEIRA_H
