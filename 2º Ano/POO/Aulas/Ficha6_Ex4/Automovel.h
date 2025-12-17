#ifndef FICHA6_EX4_AUTOMOVEL_H
#define FICHA6_EX4_AUTOMOVEL_H
#include <string>

class Automovel {
public:
    Automovel(const std:: string matricula, const std:: string marca, const std:: string combustivel, const std:: string cor);

    Automovel(const Automovel &outro);

    std::string getMatricula() const {return matricula;}
    std::string getMarca() const {return marca;}
    std::string getCombustivel() const {return combustivel;}
    std::string getCor() const {return cor;}

    std::string getString() const;

    static int getContador() {return cont;}

    Automovel &operator=(const Automovel &outro){
        marca = outro.marca;
        combustivel = outro.combustivel;
        cor = outro.cor;
        return *this;
    }

private:
    std::string matricula;
    std::string marca;
    std::string combustivel;
    std::string cor;

    static int cont;
};


#endif //FICHA6_EX4_AUTOMOVEL_H
