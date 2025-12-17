#include <iostream>
#include "Regador.h"

using namespace std;

Regador::Regador() : Ferramenta(Settings::Regador::capacidade){}

void Regador::usa(Celula &c) {

    if (gastaDose(Settings::Regador::dose)) {
        cout << "[INFO] Regador esgotado! Sera atirado para longe...\n";
    }
}