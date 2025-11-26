
#ifndef DESAFIO3_LISTA_H
#define DESAFIO3_LISTA_H

typedef struct dados no, *pno;

struct dados{
    char id[10];
    int v;
    pno prox;
};

void eliminaLista(pno lista);

pno criaLista(no tab[], int tam);

void mostraLista(pno lista);

pno desafio3(pno lista, int lim);

#endif //DESAFIO3_LISTA_H
