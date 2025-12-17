#include "Jardineiro.h"
#include "Jardim.h"

Jardineiro::Jardineiro() : pos(-1, -1), dentroDoJardim(false){

}

void Jardineiro::entra(const Posicao &p) {
    pos = p;
    dentroDoJardim = true;
}

bool Jardineiro::sai() {
    if(!dentroDoJardim)
        return false;

    pos.setPosicao(-1, -1);
    dentroDoJardim = false;
    return true;
}

bool Jardineiro::move(char dir, const Jardim &j) {

    if(!dentroDoJardim)
        return false;

    int l = pos.getLinhas();
    int c = pos.getColunas();
    int nl = l;
    int nc = c;

    if(dir == 'e'){
        nc--;
    }else if(dir == 'd'){
        nc++;
    }else if(dir == 'c'){
        nl--;
    }else if(dir == 'b'){
        nl++;
    }else{
        return false;
    }

    if(nl < 0 || nl >= j.getLinhas() || nc < 0 || nc >= j.getCols())
        return false;

    pos.setPosicao(nl, nc);
    return true;
}



