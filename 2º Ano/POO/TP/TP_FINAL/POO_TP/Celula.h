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

    //Solo
    int getAguaSolo()const {return solo.getAgua(); }
    int getNutrientesSolo() const {return solo.getNutrientes(); }

    void adicionarAguaSolo(int valor) {solo.addAgua(valor);}
    void adicionarNutrientesSolo(int valor) {solo.addNutrientes(valor);}

    const Solo& getSolo() const{return solo;}
    void setSolo(const Solo &s) {solo = s;}

    std::string descricaoSolo() const;

    //Planta
    Planta *getPlanta() const {return planta;}
    void colocarPlanta(Planta* p) { planta = p; }
    Planta *removerPlanta();


    //Ferramenta
    Ferramenta *getFerramenta() const {return ferramenta;}
    void colocarFerramenta(Ferramenta* f) { ferramenta = f; }
    Ferramenta *removerFerramenta();

    char simbolo() const;
};


#endif //POO_TP_CELULA_H
