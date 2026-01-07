#include "Celula.h"
#include "Planta.h"
#include "Ferramenta.h"

Celula::Celula() : solo(), planta(nullptr), ferramenta(nullptr){

}

Celula::~Celula(){}

Planta *Celula::removerPlanta() {
    Planta* tmp = planta;
    planta = nullptr;
    return tmp;
}

Ferramenta *Celula::removerFerramenta() {
    Ferramenta* tmp = ferramenta;
    ferramenta = nullptr;
    return tmp;
}

char Celula::simbolo() const {
    if(planta)
        return planta->getSimbolo();

    if(ferramenta)
        return ferramenta->getSimbolo();

    return ' ';
}

std::string Celula::descricaoSolo() const {return solo.descricao();}
