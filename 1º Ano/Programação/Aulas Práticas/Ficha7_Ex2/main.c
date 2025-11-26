#include <stdio.h>
#include <stdlib.h>

#include "agenda.h"

int main() {

    pct tab = NULL;
    int i, total=0;

    for(i=0; i<3; i++)
        tab = addC(tab, &total);

    listaC(tab, total);

    //printf("Contacto: %d\n", getTel(tab, total, "Ana"));

   // atualizaTel(tab, total, "Ana", 921231230);

  //  printf("Existem %d operadores moveis\n", getOperador(tab, total));

    eliminaC(tab, &total, "Diogo");
    listaC(tab, total);

    free(tab);

    return 0;
}
