#include <iostream>
#include <sstream>
#include "Agenda.h"

using namespace std;

bool Agenda::insere(string nome, string morada, int tel) {
    if(nome.empty() || morada.empty() || tel <= 0)
        return false;

    if(contactos.find(nome) != contactos.end())
        return false;

    contactos.insert({nome, Contacto(nome, morada, tel)});
        return true;
}

/*
bool Agenda::insere(std::string nome, std::string morada, int tel) {

    auto it = contactos.insert({nome, Contacto(nome, morada, tel)});
    return it.second;
}
 */

bool Agenda::elimina(string nome) {
    if(nome.empty())
        return false;

    if(contactos.find(nome) != contactos.end())
        return false;

    contactos.erase(nome);
        return true;

    //return contactos.erase(nome) == 1;
}

int Agenda::obtemTelefone(string nome) const {

    if(nome.empty())
        return -1;

    auto it = contactos.find(nome);
    if(it == contactos.end()){
        return -1;
    }

    return it->second.getTelef();
}

string Agenda::obtemMorada(string nome) const {
    if(nome.empty())
        return "";

    auto it = contactos.find(nome);
    if(it == contactos.end()){
        return "";
    }

    return it->second.getMorada();
}

bool Agenda::atualizaTelefone(string nome, int tel) {

    if(nome.empty() || tel <= 0)
        return false;

    auto it = contactos.find(nome);
    if(it == contactos.end()){
        return false;
    }

    it->second.mudaTelef(tel);
    return true;
}

bool Agenda::atualizaMorada(string nome, string morada) {
    if(nome.empty() || morada.empty())
        return false;

    auto it = contactos.find(nome);
    if(it == contactos.end()){
        return false;
    }

    it->second.mudaMorada(morada);
    return true;
}

bool Agenda::atualizaNome(string nomeAntigo, string nomeNovo) {
    if(nomeAntigo.empty() || nomeNovo.empty())
        return false;

    auto it = contactos.find(nomeAntigo);
    if(it == contactos.end() || contactos.find(nomeNovo) != contactos.end()){
        return false;
    }

    string morada = it->second.getMorada();
    int tel = it->second.getTelef();

    contactos.erase(it);
    contactos.insert({nomeNovo, Contacto(nomeNovo, morada, tel)});
    return true;
}

std::string Agenda::obtemLista() const {
    std::ostringstream oss;

    oss << "Lista de Contactos: " << endl;

    for(auto it = contactos.begin(); it != contactos.end(); it ++){

        oss << "- " << it->second.descricao() << endl;
    }

    return oss.str();
}

