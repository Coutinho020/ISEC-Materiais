#include <iostream>
#include "Pessoa.h"
#include "Presidencia.h"

using namespace std;

int main() {

    Pessoa p1("Diogo Antunes", "123456W17", 25);
    Pessoa p2 ("Antonio", "234567W18, ", 38);
    Pessoa p3 ("Ruben", "345678W19", 15);

    cout << "Vou criar a presidencia...\n";

    Presidencia presi1(p1, p2, p3);

    Presidencia presi2("nomea", "ida", 34,
                       "nomeb", "idb", 25,
                       "nomec", "idc", 17);

    cout << p1.getAsString() << endl;

    return 0;
}
