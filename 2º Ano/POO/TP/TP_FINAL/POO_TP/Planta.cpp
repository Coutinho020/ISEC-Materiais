#include "Planta.h"
#include <sstream>

using namespace std;

Planta::Planta(int agua, int nutrientes) :
        viva(true), agua(agua), nutrientes(nutrientes), prontaParaMultiplicar(false){}

void Planta::setNutrientes(int valor) {
    nutrientes = valor;
    if(nutrientes < 0){
        nutrientes = 0;
    }
}

void Planta::setAgua(int valor) {
    agua = valor;
    if(agua < 0){
        agua = 0;
    }
}

void Planta::addAgua(int valor) {
    if(!viva)
        return;

    setAgua(agua + valor);
}

void Planta::addNutrientes(int valor) {
    if(!viva)
        return;

    setNutrientes(nutrientes + valor);
}

std::string Planta::descricao() const {

    ostringstream oss;
    oss << "[Planta: " << getNome() << "] A: " << agua
        << ", N: " << nutrientes;

    return oss.str();
}





