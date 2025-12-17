#include <iostream>
#include "Clube.h"

bool Clube::registaSocio(const Pessoa *pessoa) {
    socios.push_back(pessoa);
    return true;
}
