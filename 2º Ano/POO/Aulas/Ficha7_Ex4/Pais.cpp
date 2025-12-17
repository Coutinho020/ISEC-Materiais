#include <iostream>
#include <sstream>
#include "Pais.h"

using namespace std;

auto Pais::procurarPessoa(int bi) const {
    auto it = pessoas.begin();
    while(it != pessoas.end() && (*it)->getBI() != bi)
        it++;

    return it;
}

Pais::Pais(const Pais &outro) {
    *this = outro;
}

Pais & Pais::operator=(const Pais &outro) {
    if(this != &outro)
        return *this;

    nome = outro.nome;
    apagarTodasAsPessoas();
    for(const Pessoa * pessoa : outro.pessoas)
        pessoas.push_back(new Pessoa(*pessoa));
    return *this;
}

Pais::~Pais() {
    apagarTodasAsPessoas(); //notar que pessoas.clear() nao era necessario
}

bool Pais::adicionarPessoa(const string &nome, int bi, int nif) {
    if(nome.empty() || bi <= 0 || nif <= 0)
        return false;

    auto it = procurarPessoa(bi);
    if(it != pessoas.end())
        return false;

    pessoas.push_back(new Pessoa(nome, bi, nif));
    return true;
}

bool Pais::adicionarPessoa(Pessoa *pessoa) {
    if(pessoa->getNome().empty())
        return false;

    auto it = procurarPessoa(pessoa->getBI());
    if(it != pessoas.end())
        return false;

    pessoas.push_back(pessoa);
    return true;
}

void Pais::apagarTodasAsPessoas() {
    for(Pessoa *pessoa : pessoas)
        delete pessoa;

    pessoas.clear();
}

std::string Pais::ObterNomePessoa(int bi) const {
    auto it = procurarPessoa(bi);
    if(it == pessoas.end())
        return "";

    return (*it)->getNome();
}

std::string Pais::obterLista() const {
    ostringstream oss;

    oss << "Pessoas de " << nome << ":\n";
    for(const Pessoa * pessoa : pessoas)
        oss << "- " << pessoa->descricao() << "\n";

    return oss.str();
}

bool Pais::atualizarNomePessoa(int bi, const string &nome) {
    if(nome.empty())
        return false;

    auto it = procurarPessoa(bi);
    if(it != pessoas.end())
        return false;

    (*it)->setNome(nome);
    return true;
}

const Pessoa *Pais::obterPessoa(int bi) const {
    auto it = procurarPessoa(bi);

    return it ==pessoas.end() ? nullptr : *it;
}

bool Pais::removerPessoa(int bi) {
    auto it = procurarPessoa(bi);
    if(it == pessoas.end())
        return false;

    delete *it;
    pessoas.erase(it);
    return true;
}

bool Pais::tarsferirPessoa(int bi, Pais &paisDestino) {
    auto it = procurarPessoa(bi);
    if(it == pessoas.end())
        return false;

    if(!paisDestino.adicionarPessoa(*it))
        return false;
    pessoas.erase(it);
    return true;
}








