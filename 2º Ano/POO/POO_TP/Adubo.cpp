#include "Adubo.h"
#include <iostream>

Adubo::Adubo() : Ferramenta(Settings::Adubo::capacidade){}

void Adubo::usa(Celula &c) {

    if (gastaDose(Settings::Adubo::dose)) {
        std::cout << "[INFO] Pacote de adubo vazio, varrido pelo vento.\n";
    }
}
