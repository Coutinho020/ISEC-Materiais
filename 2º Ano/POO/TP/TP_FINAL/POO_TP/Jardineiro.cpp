#include "Jardineiro.h"
#include "Jardim.h"

Jardineiro::Jardineiro() : pos(-1, -1), dentroDoJardim(false), movimentosTurno(0), entradasTurno(0), saidasTurno(0), plantacoesTurno(0), colheitasTurno(0){

}

void Jardineiro::resetTurno() {
    movimentosTurno = 0;
    entradasTurno = 0;
    saidasTurno = 0;
    plantacoesTurno = 0;
    colheitasTurno = 0;
}

bool Jardineiro::entra(const Posicao &p) {
    if(!podeEntrar())
        return false;

    pos = p;
    dentroDoJardim = true;
    entradasTurno++;
    return true;
}

bool Jardineiro::sai() {
    if(!dentroDoJardim || !podeSair())
        return false;

    pos.setPosicao(-1, -1);
    dentroDoJardim = false;
    saidasTurno++;
    return true;
}

bool Jardineiro::move(char dir, const Jardim &j) {

    if(!dentroDoJardim || !podeMover())
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
    movimentosTurno++;
    return true;
}

bool Jardineiro::PegarFerramenta(int nrSerie) {

    Ferramenta *f = inventario.pegar(nrSerie);
    if(f == nullptr)
        return false;

    return true;
}

bool Jardineiro::largarFerramenta() {
    return inventario.largar();
}

bool Jardineiro::adicionarFerramenta(Ferramenta *f) {
    if(f == nullptr)
        return false;

    return inventario.adicionar(f);
}

Ferramenta *Jardineiro::getFerramentaNaMao() const {
    return inventario.getNaMao();
}

bool Jardineiro::usarFerramentaNaMao(Celula &c) {
    Ferramenta *f = inventario.getNaMao();

    if(f == nullptr || f->jaFoiUsada())
        return false;

    if(f->usa(c)){
        f->marcarUsada();

        if(f->esgotou()){
            eliminarFerramentaNaMao();
        }
        return true;
    }
    return false;
}

void Jardineiro::eliminarFerramentaNaMao() {
    inventario.eliminarFerramentaNaMao();
}

void Jardineiro::resetUsoFerramentas() {
    inventario.resetUsoFerramentas();
}






