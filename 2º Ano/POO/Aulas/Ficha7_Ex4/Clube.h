#ifndef FICHA7_EX4_CLUBE_H
#define FICHA7_EX4_CLUBE_H
#include <string>
#include <vector>
#include "Pessoa.h"
#include "Pais.h"

class Clube {
public:
    //Clube(const std::string &nome, const Pais &pais)
    Clube(const std::string &nome) : nome(nome){}

    //bool registaSocio(int bi);
    bool registaSocio(const Pessoa *pessoa);


private:
    std::string nome;
    std::vector<const Pessoa *> socios;
    //const Pais &pais;
    //set<int> biSocios;
};


#endif //FICHA7_EX4_CLUBE_H
