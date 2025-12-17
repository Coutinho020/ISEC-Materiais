#include "Tubarao.h"
#include "Aquario.h"
#include <iostream>

using namespace std;

Tubarao::Tubarao(std::string cor) : Peixe("tubarao", cor, 15){

}

void Tubarao::alimentar(double qtGramas, Aquario *aquario) {
    if(getPeso()>20)
        setPeso(getPeso()-1);
    else if(getPeso() < 20){
        Peixe *outro = aquario->obterPeixeExcepto(getId());
        if(outro!= nullptr){
            setPeso(getPeso() + outro->getPeso());
            outro->matar();
        }else{
            setPeso(getPeso()-2);
            if(getPeso() < 5){
                matar();
            }
        }
    }
}

Peixe *Tubarao::duplicado() const {
    Tubarao *duplicado = new Tubarao(getCor()); //novo elemento
    duplicado->setPeso(getPeso());
    return duplicado;
    //Carpa *duplicado = new Carpa(*this);  //Elemento igual
}
