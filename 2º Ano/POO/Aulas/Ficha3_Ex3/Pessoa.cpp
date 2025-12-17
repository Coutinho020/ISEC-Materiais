#include <iostream>
#include <sstream>
#include "Pessoa.h"

using namespace std;

Pessoa::Pessoa(string nome, string id, int idade):
    nome(nome), id(id), idade(idade){

    cout << "Pessoa criada: " << nome << endl;
}

string Pessoa::getNome() const{
    return nome;
}

string Pessoa::getID() const{
    return id;
}

int Pessoa::getIdade() const{
    return idade;
}

bool Pessoa::setNome(string n){
    if(n.empty() || n.length()>256){
        return false;
    }
    nome = n;
    return true;
}

bool Pessoa::setIdade(int i){
    if(idade < 0 || idade > 150){
        return false;
    }
    idade = i;
    return true;
}

string Pessoa::getAsString() const {
    //Nome: Diogo Antunes; ID: 123456W7Y; Idade: 25
    /* string str = "Nome: " + nome + "; ";
    str += "ID: " + id + "; ";
    str += "Idade: " + to_string(idade);
    return str;   */

    ostringstream oss;
    oss << "Nome: " << nome << "; ";
    oss << "Id: " << id << "; ";
    oss << "Idade: " << idade;
    return oss.str();

    //istringstream iss("Diogo Antunes 25 diogo@isec.pt");
}

Pessoa::~Pessoa(){

    cout << "Pessoa destruida: " << nome << endl;
}
