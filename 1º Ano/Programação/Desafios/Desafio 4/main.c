#include <stdio.h>

#include "parque.h"

int main(){
    hora a = {0,0}, b = {0,0};
    int v1 = 0, v2 = 0;
    pCliente l1 = criaExemploED((cliente []){{13, 2, NULL, NULL},{17,1,NULL,NULL},{22,3,NULL,NULL}},
                                (acesso[] ){{{10,20},{11,52},NULL}, {{14,30},{17,2},NULL}, {{10,50},{-1,-1},NULL},
                                            {{9,11},{9,12},NULL},{{10,5},{12,0},NULL},{{14,33},{-1,-1},NULL}},
                                3);


    pCliente l2 = criaExemploED((cliente []){{13, 1, NULL, NULL},{17,2,NULL,NULL},{22,2,NULL,NULL},{25,1,NULL,NULL}},
                                (acesso[] ){{{8,20},{-1,-1},NULL}, {{9,30},{9,40},NULL}, {{10,50},{14,1},NULL},
                                            {{9,11},{9,12},NULL},{{10,5},{-1,-1},NULL},{{14,33},{14,34},NULL}},
                                4);

    // O exemplo 1 deve escrever Hora: 09:11 e Valor: 1160
    // Deve eliminar os 2 primeiros acessos do cliente 22
    if (l1 != NULL) {
        printf("Exemplo 1: \n");
        mostraTudo(l1);
        l1 = desafio4(l1, &a, 22, &v1);
        printf("Hora: %2.2d:%2.2d\nValor: %d\n", a.h, a.m, v1);
        mostraTudo(l1);
        libertaTudo(l1);
    }

    // O exemplo 2 deve escrever Hora: 08:20 e Valor: 10
    // Deve eliminar o cliente 25 e todos os seus acessos
    if (l2 != NULL) {
        printf("\nExemplo 2: \n");
        mostraTudo(l2);
        l2 = desafio4(l2, &b, 25, &v2);
        printf("Hora: %2.2d:%2.2d\nValor: %d\n", b.h, b.m, v2);
        mostraTudo(l2);
        libertaTudo(l2);
    }
    return 0;
}
