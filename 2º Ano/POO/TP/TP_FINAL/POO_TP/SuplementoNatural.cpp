#include "SuplementoNatural.h"
#include <iostream>

using namespace std;

SuplementoNatural::SuplementoNatural(): Ferramenta(capacidade){}

bool SuplementoNatural::usa(Celula &c) {

    Planta *p = c.getPlanta();
    if (p != nullptr && (p->getBeleza() == "bonita" || p->getBeleza() == "neutra")) {
        p->addNutrientes(dose_planta);
        gastaDose(dose_planta);
        return true;
    }
    return false;
}