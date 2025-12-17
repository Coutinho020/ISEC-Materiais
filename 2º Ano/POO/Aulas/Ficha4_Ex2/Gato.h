#ifndef FICHA4_EX2_GATO_H
#define FICHA4_EX2_GATO_H
#include "Animal.h"

class Gato : public Animal{

public:
    Gato(const std::string &nome, double peso, const std::string &DataNascimento);

    std::string exercitar() override;
    std::string alimentar() override;

private:
    static const int MAX_JARRAS = 3;
    static const int MIN_JARRAS = 0;
    static const int MAX_PESSOAS = 4;
    static const int MIN_PESSOAS = 4;

    static const double TAXA_EMAGRECIMENTO;
    static const double MAX_PESO;
    static const double MIN_PESO;
};


#endif //FICHA4_EX2_GATO_H
