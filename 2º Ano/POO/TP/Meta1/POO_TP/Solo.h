#ifndef POO_TP_SOLO_H
#define POO_TP_SOLO_H
#include <string>
#include "Settings.h"

class Solo {
    int agua;
    int nutrientes;

public:
    Solo();

    int getAgua() const {return agua;}
    int getNutrientes() const {return nutrientes;}

    void addAgua(int valor);
    void addNutrientes(int valor);

    std::string descricao() const;
};


#endif //POO_TP_SOLO_H
