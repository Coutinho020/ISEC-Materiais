#include <iostream>
#include "ListaCompras.h"
#include "ListaComprasVector.h"
#include "ListaComprasSet.h"

using namespace std;

int main() {

    ListaComprasSet listaA;
    listaA.adiciona("Leite", 10);
    listaA.adiciona("Acucar", 8);
    listaA.adiciona("Natas", 5);
    cout << listaA.obtemDescricao() << endl;

    listaA.elimina("Acucar");
    cout << listaA.obtemDescricao() << endl;

    listaA.removeQty("Leite", 4);
    cout << listaA.obtemDescricao() << endl;

    listaA.eliminaTodosMenoresQue(6);
    cout << listaA.obtemDescricao() << endl;

    listaA.adiciona("Laranjas", 5);
    cout << listaA.obtemDescricao() << endl;

    listaA.removeQty("Leite", 7);
    cout << listaA.obtemDescricao() << endl;

    return 0;
}
