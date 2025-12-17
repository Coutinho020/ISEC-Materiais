#ifndef FICHA4_EX2_CLINICA_H
#define FICHA4_EX2_CLINICA_H
#include "Animal.h"
#include <string>

class Clinica {

public:
    Clinica();
    bool AddAnimal(Animal &animal);
    bool RemoveAnimal(const std::string &codigo);
    const Animal *getAnimal(const std::string &codigo) const;
    std::string getDescricaoAnimal(const std::string &codigo) const;
    std::string getListaAnimais() const;
    std::string exercitarAnimais();
    std::string alimentarAnimais();

private:
    static const int MAX_ANIMAIS = 200;
    Animal *animais[MAX_ANIMAIS];
    int nrAnimais;

    int procuraAnimal(const std::string &codigo) const;
};


#endif //FICHA4_EX2_CLINICA_H
