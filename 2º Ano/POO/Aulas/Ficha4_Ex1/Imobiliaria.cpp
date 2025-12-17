#include "Imobiliaria.h"
#include <sstream>

using namespace std;

Imobiliaria::Imobiliaria() : nImoveis(0){
    for(int i = 0; i < Max_Imoveis; i++){
        imoveis[i] = nullptr;
    }
}

int Imobiliaria::procurarImovel(const string &codigo) const {
    for(int i = 0; i < nImoveis; i++){
        if(imoveis[i]->getCodigo() == codigo){
            return i;
        }
    }
    return -1;
}

bool Imobiliaria::addImovel(Imovel *imovel) {
    if(nImoveis >= Max_Imoveis || imovel == nullptr || procurarImovel(imovel->getCodigo()) != -1)
        return false;

    imoveis[nImoveis] = imovel;
    nImoveis++;
    return true;
}

bool Imobiliaria::RemoverImovel(const string &codigo){

    int i = procurarImovel(codigo);
    if(i < 0)
        return false;

    while(i < nImoveis-1){
        imoveis[i] = imoveis[i+1];
        i++;
    }
    nImoveis--;
    return true;
}

std::string Imobiliaria::ListaTodos() const {

    ostringstream oss;

    oss << " \nImoveis: " << endl;
    for(int i = 0; i < nImoveis; i++){
        oss << " \t-" << imoveis[i]->getDescricao() << endl;
    }
    return oss.str();
}

std::string Imobiliaria::ListaAndar(int andar) const {
    ostringstream oss;
    oss << "Imoveis do andar: " << andar;
    for(int i = 0; i < nImoveis; i++){
        if(imoveis[i]->getAndar() == andar){
            oss << "\t- " << imoveis[i] -> getDescricao() << endl;
        }
    }
    return oss.str();
}

std::string Imobiliaria::getDescricaoImovel(const string &codigo) const {

    int i = procurarImovel(codigo);
    if (i < 0)
        return "";

    return imoveis[i]->getDescricao();
}

const Imovel *Imobiliaria::getImovel(const string &codigo) const {

    int i = procurarImovel(codigo);
    if(i < 0)
        return nullptr;

    return imoveis[i];
}

void Imobiliaria::aumentarPrecos() {
    for(int i = 0; i < nImoveis; i++)
        imoveis[i]->aumentarPreco();
}
