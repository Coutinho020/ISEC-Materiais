#include "Peixe.h"
#include <iostream>
#include <sstream>

using namespace std;

int Peixe::contadorId = 1000;

Peixe::Peixe(std::string especie, std::string cor, double peso) :
    especie(especie), cor(cor), peso(peso), id(contadorId++), vivo(true){

}

Peixe::Peixe(const Peixe &p) :
        especie(p.especie), cor(p.cor), peso(p.peso), id(p.id), vivo(p.vivo){

}

std::string Peixe::getDescricao() const {
    return especie + " " + to_string(id);
}

void Peixe::setPeso(double peso) {
    this->peso = peso;
}
