#ifndef POO_TP_CELULA_H
#define POO_TP_CELULA_H
#include "Solo.h"

class Planta;
class Ferramenta;

class Celula {

    Solo solo;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    Celula();
    ~Celula();

    Solo& getSolo() {return solo; }
    const Solo& getSolo() const {return solo; }

    Planta* getPlanta() const { return planta; }
    Ferramenta* getFerramenta() const { return ferramenta; }

    void setPlanta(Planta* p) { planta = p; }
    void setFerramenta(Ferramenta* f) { ferramenta = f; }

    char simbolo() const;
};


#endif //POO_TP_CELULA_H
