#include "Solo.h"
#include <sstream>
#include <cstdlib>

using namespace std;

Solo::Solo() : agua(Settings::Jardim::agua_min + (rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1))),
               nutrientes(Settings::Jardim::nutrientes_min + (rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1))){

}

void Solo::addAgua(int valor) {
    agua += valor;
    if(agua < 0)
        agua = 0;
}

void Solo::addNutrientes(int valor) {
    nutrientes += valor;
    if(nutrientes < 0)
        nutrientes = 0;
}

string Solo::descricao() const{

    ostringstream oss;

    oss << "Agua: " << agua << " Nutrientes: " << nutrientes;

    return oss.str();
}


