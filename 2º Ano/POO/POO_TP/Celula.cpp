#include "Celula.h"

Celula::Celula() : solo(), planta(nullptr), ferramenta(nullptr){

}

Celula::~Celula(){}

char Celula::simbolo() const {
    if(planta)
        return 'p';

    if(ferramenta)
        return 'f';

    return '.';
}
