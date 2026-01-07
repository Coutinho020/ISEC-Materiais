#include "Inventario.h"
#include <sstream>
#include <iostream>

using namespace std;

Inventario::Inventario() : naMao(nullptr) {

}

Inventario::Inventario(const Inventario& outro) : naMao(nullptr){
    copia(outro);
}

vector<Ferramenta *>::iterator Inventario::procurar(int nrSerie) {
    auto it = ferramentas.begin();

    while(it != ferramentas.end() && (*it)->getNrSerie() != nrSerie){
        it++;
    }
    return it;
}

void Inventario::libertar(){
    for (Ferramenta *f : ferramentas)
        delete f;
    ferramentas.clear();

    if (naMao != nullptr) {
        delete naMao;
        naMao = nullptr;

    }
}

void Inventario::copia(const Inventario& outro) {
    for(Ferramenta *f : outro.ferramentas){
        if(f != nullptr)
            ferramentas.push_back(f->clone());
    }

    if(outro.naMao != nullptr){
        naMao = outro.naMao->clone();
    }else{
        naMao = nullptr;
    }
}

Inventario& Inventario::operator=(const Inventario& outro) {
    if (this != &outro) {
        libertar();
        copia(outro);
    }
    return *this;
}

bool Inventario::adicionar(Ferramenta* f) {
    if(f == nullptr)
        return false;

    ferramentas.push_back(f);
    return true;
}

Ferramenta* Inventario::pegar(int nrSerie) {
    auto it = procurar(nrSerie);
    if(it == ferramentas.end())
        return nullptr;

    Ferramenta *escolhida = *it;
    ferramentas.erase(it);

    if(naMao != nullptr)
        ferramentas.push_back(naMao);

    naMao = escolhida;
    return naMao;
}

bool Inventario::largar() {
    if(naMao == nullptr)
        return false;

    ferramentas.push_back(naMao);
    naMao = nullptr;
    return true;
}


std::string Inventario::descricao() const {
    ostringstream oss;
    oss << "\n--- Inventario ---\n";

    if (naMao) {
        oss << "Na Mao (ATIVA): " << naMao->descricao() << "\n";
    } else {
        oss << "Na Mao (ATIVA): Nenhuma.\n";
    }

    oss << "Ferramentas transportadas:\n";
    for (auto f : ferramentas)
        oss << "  " << f->descricao() << "\n";

    if (ferramentas.empty())
        oss << "  (vazio)\n";

    return oss.str();
}

void Inventario::resetUsoFerramentas() {

    for(auto f : ferramentas){
        if(f != nullptr)
            f->resetUso();
    }
    if(naMao != nullptr)
        naMao->resetUso();
}

void Inventario::eliminarFerramentaNaMao() {
    if(naMao != nullptr){
        delete naMao;
        naMao = nullptr;
    }
}

Inventario::~Inventario() {
   libertar();
}

