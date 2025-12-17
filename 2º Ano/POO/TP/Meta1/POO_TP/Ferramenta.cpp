#include "Ferramenta.h"
#include <sstream>

using namespace std;

int Ferramenta::contadorSerie = 1;

Ferramenta::Ferramenta(int recursos) :nrSerie(contadorSerie++), recursos(recursos) {}

bool Ferramenta::gastaDose(int dose) {
    if (recursos == USOS_ILIMITADOS) {
        return false;
    }
    recursos -= dose;

    if (recursos <= 0) {
        recursos = 0;
        return true;
    }
    return false;
}


std::string Ferramenta::descricao() const {
    ostringstream oss;
    oss << "[Ferramenta: " << getNome() << "] Nr Serie: " << nrSerie;

    if (recursos == USOS_ILIMITADOS) {
        oss << ", Duracao: Ilimitada.";
    } else {
        oss << ", Recursos Restantes: " << recursos;
    }
    return oss.str();
}
