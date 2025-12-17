#include "Gato.h"
#include <sstream>
#include <cstdlib>

using namespace std;

const double Gato::TAXA_EMAGRECIMENTO = -0.1;
const double Gato::MAX_PESO = 999;
const double Gato::MIN_PESO = 2.5;

Gato::Gato(const std::string &nome, double peso, const std::string &dataNascimento) :
    Animal("gato", nome, peso, dataNascimento){

}

std::string Gato::alimentar() {
    return "o que, este pate reles novamente?";
}

std::string Gato::exercitar() {

    setPeso(TAXA_EMAGRECIMENTO, MIN_PESO, MAX_PESO);

    ostringstream oss;
    int jarras = MIN_JARRAS + rand() % (MAX_JARRAS - MIN_JARRAS + 1);
    int pessoas = MIN_PESSOAS + rand() % (MAX_PESSOAS - MIN_PESSOAS + 1);

    oss << "derrubei " << jarras << " jarras e arranhei " << pessoas << " pessoas";

    return oss.str();
}
