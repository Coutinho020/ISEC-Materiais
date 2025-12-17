#include "Imovel.h"
#include <sstream>
#include <iomanip>

using namespace std;

unsigned int Imovel::contador = 1;

Imovel::Imovel(const string &prefixo, double area, double preco, int andar) :
        codigo(getNovoCodigo(prefixo)), area(area), preco(preco), andar(andar){
    //getNovoCodigo(prefixo);
}

string Imovel::getNovoCodigo(const std::string &prefixo) {
    ostringstream oss;
    oss << prefixo << setw(5) << setfill('0') << ++contador;
    return oss.str();
}

std::string Imovel::getDescricao() const {
    ostringstream oss;

    oss << " Codigo: " << codigo << ";"
        << " Preco: " << preco << ";"
        << " Area: " << area << ";"
        << " Andar: " << andar;

    return oss.str();
}

void Imovel::aumentarPreco() {

    preco *= 1 + getPercentagem();
}


