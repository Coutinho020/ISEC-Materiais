#include "Animal.h"
#include <sstream>

using namespace std;

int Animal::contador = 1000;

Animal::Animal(const std::string &tipo, const std::string &nome, double peso, const std::string &dataNascimento) :
    codigo(getNovoCodigo(tipo)) , nome(nome), peso(peso),
    dataNascimento(dataNascimento){
        if(peso < 0)
            throw invalid_argument("Peso invalido");
        if(nome.empty())
            throw invalid_argument("Nome invalido");
    if(dataNascimento.empty())
        throw invalid_argument("Data de Nascimento invalido");
    if(tipo.empty())
        throw invalid_argument("Especie invalido");
}

std::string Animal::getNovoCodigo(const string &tipo) {
    ostringstream oss;
    oss << contador++ << "-" << tipo;
    return oss.str();
}

std::string Animal::getDescricao() const {

    ostringstream oss;
    oss << getEspecie() << " : " << "\n"
        << "Codigo: " << codigo << "\n"
        << "Nome: " << nome << "\n"
        << "Peso: " << peso << " Kg\n"
        << "Data de Nascimento: " << dataNascimento << endl;

    return oss.str();
}

std::string Animal::getEspecie() const {
    return codigo.substr(codigo.find('-')+1);
}

void Animal::setPeso(double percentagem, double minPeso, double maxPeso) {
    double novoPeso = peso * (1 + percentagem);
    if(novoPeso < minPeso)
        novoPeso = minPeso;

    if(novoPeso > maxPeso)
        novoPeso = maxPeso;
}

