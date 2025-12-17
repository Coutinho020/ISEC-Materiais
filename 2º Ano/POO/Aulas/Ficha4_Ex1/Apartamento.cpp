#include "Apartamento.h"
#include <sstream>

using namespace std;

Apartamento::Apartamento(double area, int andar, unsigned int assoalhadas) :
                Imovel("apartamento", area, 10*area, andar),
                assoalhadas(assoalhadas){
    if(assoalhadas <= 0)
        throw invalid_argument ("Numero de assoalhadas erradas");
}

string Apartamento::getDescricao() const {
    ostringstream oss;

    oss << "[Apartamento]" << Imovel::getDescricao()
        << "; Assoalhadas: " << assoalhadas;

    return oss.str();
}

double Apartamento::getPercentagem() {

    return assoalhadas / 100.0;
}
