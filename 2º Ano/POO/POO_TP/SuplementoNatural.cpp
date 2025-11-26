#include "SuplementoNatural.h"
#include <iostream>

using namespace std;

SuplementoNatural::SuplementoNatural(): Ferramenta(75){}

void SuplementoNatural::usa(Celula &c) {

    cout << "[INFO] Suplemento Natural usado. Efeito sera calculado no proximo instante.\n";
}