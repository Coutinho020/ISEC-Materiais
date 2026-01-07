#include "Adubo.h"
#include <iostream>

Adubo::Adubo() : Ferramenta(Settings::Adubo::capacidade){}

bool Adubo::usa(Celula &c) {

    c.adicionarNutrientesSolo(Settings::Adubo::dose);
    gastaDose(Settings::Adubo::dose);
    return true;
}
