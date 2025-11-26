#ifndef POO_TP_CACTO_H
#define POO_TP_CACTO_H
#include "Planta.h"
#include "Settings.h"
#include "Celula.h"

class Cacto : public Planta {
private:

    int instantesAguaExcessiva;
    int instantesNutrientesZero;

public:

    Cacto();

    char getSimbolo() const override { return 'c'; }
    std::string getNome() const override { return "Cacto"; }
    std::string getBeleza() const override { return "neutra"; }

    void processaInstante(Celula &c) override; // Esqueleto para a Meta 1
};

#endif //POO_TP_CACTO_H
