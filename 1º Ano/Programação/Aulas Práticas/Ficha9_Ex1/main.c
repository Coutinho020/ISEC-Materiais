#include <stdio.h>
#include <stdlib.h>

#include "parque.h"


int main(){
    int x, minutos;
    hora a = {10, 30};
    pCliente lista = criaExemploED();

    if (lista == NULL)
        return 0;

    mostraTudo(lista);

    // Alinea a)
    printf("\nExistem %d clientes dentro do parque\n", dentroParque(lista));

    // Alinea b)
    printf("As %2.2d:%2.2d estavam %d clientes no parque\n", a.h, a.m, dentroParqueHora(lista, a));

    // Alinea c)
    x = maisMinutos(lista, &minutos);
    if(x == -1)
        printf("\nNao existem clientes com utilizacoes completas\n");
    else
        printf("\nO cliente %d passou %d minutos no parque\n", x, minutos);

    // Alinea d)
    // lista = eliminaCliente(lista, 22);

  //  elimina_sessoes_abertas(lista);
   // mostraTudo(lista);

    // Alinea f)
    lista = acessoParque(lista, 17, (hora){17,03});
    lista = acessoParque(lista, 13, (hora){18,05});
    lista = acessoParque(lista, 19, (hora){18,15});
    mostraTudo(lista);


    libertaTudo(lista);
    return 0;
}
