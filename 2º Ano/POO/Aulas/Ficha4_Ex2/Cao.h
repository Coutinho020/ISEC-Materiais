#ifndef FICHA4_EX2_CAO_H
#define FICHA4_EX2_CAO_H
#include "Animal.h"

class Cao : public Animal {

public:
    Cao(const std::string &nome, double peso, const std::string &DataNascimento);

    std::string exercitar() override;
    std::string alimentar() override;

};


#endif //FICHA4_EX2_CAO_H
