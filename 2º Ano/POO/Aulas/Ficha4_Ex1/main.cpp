#include <iostream>
#include "Apartamento.h"
#include "Loja.h"
#include "Imobiliaria.h"

using namespace std;

int main() {

    Apartamento a(123, 2, 4);
    Loja l(23);

    cout << a.getDescricao() << endl;
    cout << l.getDescricao() << endl;

    a.aumentarPreco();
    cout << a.getDescricao() << endl;

    Imobiliaria Remax;

    Remax.addImovel(&a);
    Remax.addImovel(&l);

    Remax.aumentarPrecos();
    cout << Remax.ListaTodos() << endl;

    return 0;
}
