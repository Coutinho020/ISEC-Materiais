#include "Ferramenta.h"
#include <sstream>

using namespace std;

int Ferramenta::contadorSerie = 1;

Ferramenta::Ferramenta(int recursos) : nrSerie(contadorSerie++), recursos(recursos), usadaNesteInstante(false) {}

void Ferramenta::gastaDose(int dose) {
    if (recursos == USOS_ILIMITADOS) {
        return;
    }
    recursos -= dose;

    if(recursos < 0)
        recursos = 0;
}

bool Ferramenta::esgotou() const {
    return recursos != USOS_ILIMITADOS && recursos <= 0;
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

