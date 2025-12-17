#include "Clinica.h"
#include <sstream>

using namespace std;

Clinica::Clinica() : nrAnimais(0){

    for(int i = 0; i < MAX_ANIMAIS; i++){
        animais[i] = nullptr;
    }
}

int Clinica::procuraAnimal(const string &codigo) const {

    for(int i = 0; i < nrAnimais; i++){
        if(animais[i]->getcodigo() == codigo)
            return i;
    }
    return -1;
}

bool Clinica::AddAnimal(Animal &animal) {

    if(nrAnimais >= MAX_ANIMAIS || procuraAnimal(animal.getcodigo()) != -1)
        return false;

    animais[nrAnimais] = &animal;
    nrAnimais++;
    return true;
}

bool Clinica::RemoveAnimal(const string &codigo) {

    int i = procuraAnimal(codigo);
    if(i == -1)
        return false;

    for(int j = i; j < nrAnimais - 1; i++){
        animais[j] = animais[j + 1];
    }

    animais[nrAnimais-1] = nullptr;
    nrAnimais--;
    return true;
}

const Animal *Clinica::getAnimal(const string &codigo) const {

    int i = procuraAnimal(codigo);
    if(i == -1)
        return nullptr;

    return animais[i];
}

std::string Clinica::getDescricaoAnimal(const string &codigo) const {
    int i = procuraAnimal(codigo);
    if(i == -1)
        return "";

    return animais[i]->getDescricao();
}

std::string Clinica::getListaAnimais() const {
    ostringstream oss;

    for(int i = 0; i < nrAnimais; i++){
        oss << animais[i]->getDescricao() << "\n";
    }

    return oss.str();
}

std::string Clinica::exercitarAnimais() {
    ostringstream oss;
    for(int i = 0; i < nrAnimais; i++)
        oss << animais[i]->getcodigo() << " => "
            << animais[i]->exercitar() << (i < nrAnimais-1 ? "\n":"");
    return oss.str();
}

std::string Clinica::alimentarAnimais() {
    ostringstream oss;
    for(int i = 0; i < nrAnimais; i++)
        oss << animais[i]->getcodigo() << " => "
            << animais[i]->alimentar() << "\n";
    return oss.str();
}
