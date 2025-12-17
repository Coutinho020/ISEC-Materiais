#include "ListaComprasSet.h"
#include <iostream>
#include <sstream>

using namespace std;

bool operator<(const Coisa &coisa1, const Coisa &coisa2) {
    return coisa1.getNome() < coisa2.getNome();
}
/*
auto ListaComprasSet::procuraCoisa(const string &nome) {
    auto it = itens.begin();
    while(it != itens.end() && it->getNome() != nome)
        ++it;
    return it;
}
*/

auto ListaComprasSet::procuraCoisa(const string &nome) {
    return itens.find(Coisa(nome, 0));
}

bool ListaComprasSet::adiciona(std::string nome, int qty) {
    if(nome.empty() || qty < 1)
        return false;
    auto it = procuraCoisa(nome);
    if(it != itens.end()){
        qty += it->getQty();
        itens.erase(it);
    }
    //nao existe, tem de adicionar
    itens.insert(Coisa(nome, qty));
    return true;
}

bool ListaComprasSet::removeQty(std::string nome, int qty) {
    if(nome.empty() || qty < 1)
        return false;
    auto it = procuraCoisa(nome);
    if(it != itens.end()){
        Coisa nova = Coisa(nome, it->getQty() - qty);
        itens.erase(it);
        if(nova.getQty()>0)
            itens.insert(nova);
        return true;
    }
    return false;
}

bool ListaComprasSet::elimina(std::string nome) {
    if(nome.empty())
        return false;

    auto it = procuraCoisa(nome);
    if(it != itens.end()){
        itens.erase(it);
        return true;
    }
    return false;
}

int ListaComprasSet::eliminaTodosMenoresQue(int qty) {
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

std::string ListaComprasSet::obtemDescricao() const {
    ostringstream oss;
    int i = 0;
    oss << "Lista de Compras (set): " << endl;
    for(const Coisa & item : itens){
        if(!item.getNome().empty())
            oss << "[ITEM " << i+1 << "] : " << item.getNome() << " | Quantidade: " << item.getQty() << endl;
        i++;
    }
    return oss.str();
}

