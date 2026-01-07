#include <iostream>
#include "Regador.h"

using namespace std;

Regador::Regador() : Ferramenta(Settings::Regador::capacidade){}

bool Regador::usa(Celula &c) {
    c.adicionarAguaSolo(Settings::Regador::dose);
    gastaDose(Settings::Regador::dose);
    return true;
}