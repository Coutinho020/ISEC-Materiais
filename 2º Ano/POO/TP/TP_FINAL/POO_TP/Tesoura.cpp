#include "Tesoura.h"

Tesoura::Tesoura() : Ferramenta(USOS_ILIMITADOS){}

bool Tesoura::usa(Celula &c) {

    Planta *p = c.getPlanta();

    if (p != nullptr && p->getBeleza() == "feia") {
        delete c.removerPlanta();
        return true;
    }
    return false;
}
