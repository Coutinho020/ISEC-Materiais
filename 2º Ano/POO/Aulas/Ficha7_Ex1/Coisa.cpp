#include <iostream>
#include <sstream>
#include "Coisa.h"

using namespace std;

Coisa::Coisa(string n, int q) : nome(n), qty (q > 0? q : 0) {}

string Coisa::getNome() const { return nome; }

int Coisa::getQty () const { return qty; }

void Coisa::atualizaQty (int dif) {
    qty += dif;
    if (qty < 0)
        qty = 0;
}
string Coisa::descricao() const {
    return nome + " " + to_string(qty);
}
