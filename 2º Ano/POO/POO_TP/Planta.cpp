#include "Planta.h"
#include <sstream>

using namespace std;

Planta::Planta(int agua, int nutrientes) :
        viva(true), agua(agua), nutrientes(nutrientes),
        nutrientesAbsorvidosVida(0), aguaAbsorvidaVida(0) {}

std::string Planta::descricao() const {

    ostringstream oss;
    oss << "[Planta: " << getNome() << "] A: " << agua
        << ", N: " << nutrientes
        << ", Viva: " << (viva ? "sim" : "nao")
        << " (Total Abs.: " << nutrientesAbsorvidosVida << "N/" << aguaAbsorvidaVida << "A)";
    return oss.str();
}
