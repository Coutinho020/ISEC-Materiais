#include "Contacto.h"
#include <iostream>
#include <sstream>

using namespace std;

Contacto::Contacto(string n, string m, int tel) : nome (n), morada(m), telef(tel) {

}

string Contacto::getNome() const { return nome; }

string Contacto::getMorada() const { return morada; }

int Contacto::getTelef() const { return telef; }

void Contacto::mudaMorada(string m) { morada = m; }

void Contacto::mudaTelef(int tel) { telef = tel; }

string Contacto::descricao() const {
    return nome + " " + morada + " " + to_string(telef);
}

