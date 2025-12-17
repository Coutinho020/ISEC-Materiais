#include <iostream>
#include "Automovel.h"

using namespace std;

int main() {

    Automovel a("31-26_VM", "Citroen", "Gasoleo", "Branco");
    Automovel b("GJ-12_47", "Opel", "Gasolina", "Preto");

    b = a;

    cout << b.getString();

    return 0;
}
