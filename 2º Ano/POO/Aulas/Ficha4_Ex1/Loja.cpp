#include "Loja.h"

using namespace std;

Loja::Loja(double area) : Imovel("loja", area, area*15){

}

string Loja::getDescricao() const {

    return "[Loja] " + Imovel::getDescricao();
}

double Loja::getPercentagem() {

    return 0.01;
}
