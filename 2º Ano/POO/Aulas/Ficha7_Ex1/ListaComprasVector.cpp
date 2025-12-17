#include "ListaComprasVector.h"
#include <iostream>
#include <sstream>

using namespace std;

auto ListaComprasVector::procurarCoisa(const std::string &nome) {
    auto it = itens.begin();
    while(it != itens.end() && it->getNome() != nome)
        ++it;
    return it;
}

bool ListaComprasVector::adiciona(std::string nome, int qty) {
    if(nome.empty() || qty < 1)
        return false;

    auto it = procurarCoisa(nome);
    if(it != itens.end()){
        it->atualizaQty(qty);
        return true;
    }
    //nao existe, tem de adicionar
    itens.push_back(Coisa(nome, qty));
    return true;
}

bool ListaComprasVector::removeQty(std::string nome, int qty) {
    if(nome.empty() || qty < 1)
        return false;

    auto it = procurarCoisa(nome);
    if(it != itens.end()){
        it->atualizaQty(-qty);
        if(it->getQty()==0){
            itens.erase(it);
        }
        return true;
    }
    return false;
}

bool ListaComprasVector::elimina(std::string nome) {
    if(nome.empty())
        return false;

    auto it = procurarCoisa(nome);
    if(it != itens.end()){
        itens.erase(it);
        return true;
    }
    return false;
}

int ListaComprasVector::eliminaTodosMenoresQue(int qty) {
    int cont = 0;
    auto it = itens.begin();
    while(it != itens.end()){
        if(it->getQty()<qty){
            it = itens.erase(it);  //Quando apaga 1 devolve logo a posição do proximo elemento
            cont++;
        }else{
            ++it;
        }
    }
    return cont;
}

std::string ListaComprasVector::obtemDescricao() const {
    ostringstream oss;
    int i = 0;
    oss << "Lista de Compras (Vector): " << endl;
    for(const Coisa & item : itens){
        if(!item.getNome().empty())
            oss << "[ITEM " << i+1 << "] : " << item.getNome() << " | Quantidade: " << item.getQty() << endl;
            i++;
    }
    return oss.str();
}



