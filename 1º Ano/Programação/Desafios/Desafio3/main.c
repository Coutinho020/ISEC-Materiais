#include <stdio.h>
#include "lista.h"


int main() {
    pno l1=NULL, l2=NULL, l3=NULL, l4 = NULL;

    // Exemplo 1
    // Lista Inicial: { ABCD-50,	DE-3,	GHIJ-1,	XXYYZZ-6,	LLL-7,	R-40}
    // Lista Final: { R-40,	DE-3,	LLL-7}
    l1 = criaLista((no[]){{"ABCD",50, NULL},{"DE",3, NULL},{"GHIJ",1, NULL},{"XXYYZZ",6, NULL},{"LLL",7, NULL}, {"R",40, NULL}}, 6);
    printf("\n\nLista 1 inicial:\n");
    mostraLista(l1);
    l1 = desafio3(l1, 3);
    printf("\nLista 1 final: \n");
    mostraLista(l1);

    // Exemplo 2
    // Lista Inicial: { AAAA-5,	DD-1}
    // Lista Final: { AAAA-5,	DD-1}
    l2 = criaLista((no[]){{"AAAA",5, NULL},{"DD",1, NULL}}, 2);
    printf("\n\nLista 2 inicial:\n");
    mostraLista(l2);
    l2 = desafio3(l2, 5);
    printf("\nLista 2 final: \n");
    mostraLista(l2);

    // Exemplo 3
    // Lista Inicial: { AA-5,	DD-6,	X-7}
    // Lista Final: { X-7}
    l3 = criaLista((no[]){{"AA",5, NULL},{"DD",6, NULL},{"X",7, NULL}}, 3);
    printf("\n\nLista 3 inicial:\n");
    mostraLista(l3);
    l3 = desafio3(l3, 1);
    printf("\nLista 3 final: \n");
    mostraLista(l3);

    // Exemplo 4
    // Lista Inicial: { AA-5,	ABCDE-3,	BBBBB-1,	DD-6,	XYZ-7}
    // Lista Final: { XYZ-7,	AA-5,	DD-6}
    l4 = criaLista((no[]){{"AA",5, NULL},{"ABCDE",3, NULL},{"BBBBB",1, NULL},{"DD",6, NULL},{"XYZ",7, NULL}}, 5);
    printf("\n\nLista 4 inicial:\n");
    mostraLista(l4);
    l4 = desafio3(l4, 4);
    printf("\nLista 4 final: \n");
    mostraLista(l4);

    eliminaLista(l1);
    eliminaLista(l2);
    eliminaLista(l3);
    eliminaLista(l4);
    return 0;
}
