#include "Aquario.h"
#include <iostream>

using namespace std;

Aquario::~Aquario() {
    apagarTodosOsPeixes();
}

void Aquario::apagarTodosOsPeixes() {
    for(Peixe *peixe: peixes)
        delete peixe;

    peixes.clear();
}

void Aquario::alimentarPeixes(double qtGramas) {
    vector<Peixe *> copia(peixes);
    for(int i = 0; i < copia.size(); i++){
        copia[i]->alimentar(qtGramas, this);
    }
}

void Aquario::removerPeixesMortos() {
    auto it = peixes.begin();
    while(it != peixes.end()){
        if((*it)->estaVivo())
            ++it;
        else{
            delete *it;
            it = peixes.erase(it);
        }
    }
}



