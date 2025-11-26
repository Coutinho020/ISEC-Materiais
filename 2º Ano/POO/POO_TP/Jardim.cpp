#include "Jardim.h"

using namespace std;

Jardim::Jardim() : lins(0), cols(0), celulas(nullptr){

}

Jardim::~Jardim(){
    if(celulas != nullptr){
        delete[] celulas;
        celulas = nullptr;
    }
}

bool Jardim::inicializa(int l, int c) {

    if(l <= 0 || c <= 0 || l > MAX_LINS || c > MAX_COLS)
        return false;

    if(celulas != nullptr){
        delete[] celulas;
        celulas = nullptr;
    }

    lins = l;
    cols = c;

    celulas = new Celula[lins * cols];
    return true;
}

int Jardim::index(int l, int c) const {
    return l * cols + c;
}

Celula &Jardim::aceder(int l, int c) {
    return celulas[index(l, c)];
}

const Celula &Jardim::aceder(int l, int c) const{
    return celulas[index(l, c)];
}

void Jardim::print() const {
    if(celulas == nullptr) {
        cout << "(jardim nao criado)\n";
        return;
    }

    cout << "  ";

    for(int c = 0; c < cols; c++)
        cout << char('A' + c) << " ";
    cout << "\n";

    for(int l = 0; l < lins; l++){
        cout << char('A' + l) << " ";
        for(int c = 0 ; c < cols; c++){
            if(jardineiro.estaNoJardim() && jardineiro.getPos().getLinhas() == l && jardineiro.getPos().getColunas() == c){
                cout << "*" << " ";
            }else{
                cout << celulas[index(l,c)].simbolo() << " ";
            }
        }
        cout << "\n";
    }
}

bool Jardim::PosicaoValida(int l, int c) const {
    return l >= 0 && l < lins && c >= 0 && c < cols;
}
