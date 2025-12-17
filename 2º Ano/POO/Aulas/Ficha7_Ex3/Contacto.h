#ifndef FICHA7_EX3_CONTACTO_H
#define FICHA7_EX3_CONTACTO_H
#include <string>

class Contacto {
public:
    Contacto(std::string n, std::string m, int tel);
    std::string getNome() const;
    std::string getMorada() const;
    int getTelef() const;
    void mudaMorada(std::string m);
    void mudaTelef(int tel);
    std::string descricao() const;
private:
    std::string nome;
    std::string morada;
    int telef;
};


#endif //FICHA7_EX3_CONTACTO_H
