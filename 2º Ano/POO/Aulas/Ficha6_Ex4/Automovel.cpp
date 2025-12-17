#include "Automovel.h"
#include <sstream>

using namespace std;

int Automovel::cont = 0;

Automovel::Automovel(const std::string matricula, const std::string marca, const std::string combustivel,const std::string cor) :
    matricula(matricula), marca(marca), combustivel(combustivel), cor(cor){

    cont++;
}

Automovel::Automovel(const Automovel &outro) :
    matricula(outro.matricula), marca(outro.marca), combustivel(outro.combustivel), cor(outro.cor){

    cont++;
}

std::string Automovel::getString() const {
    std::ostringstream oss;

    oss << "Marca: " << marca << endl;
    oss << "Matricula: " << matricula << endl;
    oss << "Combustivel: " << combustivel << endl;
    oss << "Cor: " << cor << endl;

    return oss.str();
}

