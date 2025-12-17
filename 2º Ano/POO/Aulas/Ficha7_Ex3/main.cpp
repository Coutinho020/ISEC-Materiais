#include <iostream>
#include "Agenda.h"

using namespace std;

int main() {

    Agenda a1;

    a1.insere("Joao", "Viseu", 969216465);
    a1.insere("Antonio", "Coimbra", 929766445);

    cout << a1.obtemLista();

    

    return 0;
}
