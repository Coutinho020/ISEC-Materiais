#include "Carpa.h"
#include "Aquario.h"
#include <iostream>

using namespace std;

Carpa::Carpa(std::string cor) : Peixe("carpa", cor, 5) {

}

void Carpa::alimentar(double qtGramas, Aquario *aquario) {
    setPeso(getPeso() + qtGramas);

    if(getPeso() > 50){
        aquario->adicionarPeixe(*new Carpa(getCor()));
        setPeso(20);
    }
}

Peixe *Carpa::duplicado() const {
    Carpa *duplicado = new Carpa(getCor()); //novo elemento
    duplicado->setPeso(getPeso());
    return duplicado;
    //Carpa *duplicado = new Carpa(*this);  //Elemento igual
}
