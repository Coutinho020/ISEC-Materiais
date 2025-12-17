#include "ListaCompras.h"
#include "ListaComprasVector.h"

#include <sstream>

using namespace std;

int ListaCompras::procuraCoisas(const string &nome) const {
    for(int i = 0; i < MAX_COISAS; i++){
        if(itens[i].getNome() == nome){
            return i;
        }
    }
    return -1;
}

bool ListaCompras::adiciona(string nome, int qty) {
    if(nome.empty() || qty < 1){
        return false;
    }
    int pos = procuraCoisas(nome);

    if(pos == -1){
        for(int i = 0; i < MAX_COISAS; i++){
            if(itens[i].getNome().empty()){
                itens[i] = Coisa(nome, qty);
                return true;
            }
        }
    }else{
        itens[pos].atualizaQty(qty);
        return true;
    }
    return false;
}

bool ListaCompras::removeQty(string nome, int qty) {
    if(nome.empty() || qty < 1){
        return false;
    }
    int pos = procuraCoisas(nome);

    if(pos != -1){
        itens[pos].atualizaQty(-qty);
        if(itens[pos].getQty()==0)
            itens[pos] = Coisa();
        return true;
    }

    return false;
}

bool ListaCompras::elimina(string nome) {

    if(nome.empty())
        return false;

    int pos = procuraCoisas(nome);

    if(pos != -1){
     itens[pos] = Coisa();
     return true;
    }
    return false;
}
/*
int ListaCompras::eliminaTodosMenoresQue(int qty) {

    int cont = 0;

    if(qty < 1)
        return 0;

    for(int i = 0; i < MAX_COISAS; i++){
        if(itens[i].getQty() < qty){
            itens[i] = Coisa();
            cont++;
        }
    }
    return cont;
}
*/
int ListaCompras::eliminaTodosMenoresQue(int qty) {
    //array<Coisa, MAX_COISAS>::iterator it = itens.begin();
    auto it = itens.begin();
    int cont = 0;
    while(it != itens.end()){
        if(it->getQty()<qty){
            *it = Coisa();
            cont++;
        }
        ++it;
    }
    return cont;
}

string ListaCompras::obtemDescricao() const {
    ostringstream oss;

    oss << "Lista de Compras: " << endl;
    for(int i = 0; i < MAX_COISAS; i++){
        if(!itens[i].getNome().empty())
            oss << "[ITEM " << i+1 << "] : " << itens[i].getNome() << " | Quantidade: " << itens[i].getQty() << endl;
    }
    return oss.str();
}

Coisa ListaCompras::obtemAt(int posição) {

    if(posição < 0 || posição >= MAX_COISAS)
        return Coisa("", 0);

    if(!itens[posição].getNome().empty())
        return itens[posição];

    return Coisa();
}




