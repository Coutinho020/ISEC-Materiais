
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

// Nome: Diogo Coutinho Amor Antunes
// Número: 2018016615

void eliminaLista(pno lista){
    pno aux;

    while(lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

pno criaLista(no tab[], int tam){
    int i;
    pno lista=NULL, novo;

    for(i=tam-1; i>=0; i--){
        novo = malloc(sizeof(no));
        if(novo == NULL){
            eliminaLista(lista);
            return NULL;
        }
        *novo = tab[i];
        novo->prox = lista;
        lista = novo;
    }
    return lista;
}

void mostraLista(pno lista){
    printf("{ ");
    while(lista != NULL){
        printf("%s-%d", lista->id, lista->v);
        lista = lista->prox;
        if(lista!=NULL)
            printf(",\t");
    }
    printf("}");
}


pno desafio3(pno lista, int lim){

    pno atual = lista, anterior = NULL, aux;

    while(atual != NULL){
        if(strlen(atual->id) > lim){
            aux = atual;
            if(anterior == NULL){
                lista = atual->prox;
                atual = lista;
            } else {
                anterior->prox = atual->prox;
                atual = atual->prox;
            }
            free(aux);
        }else{
            anterior = atual;
            atual = atual->prox;
        }
    }

    int cont = 0;
    atual = lista;
    while(atual != NULL){
        cont++;
        atual = atual->prox;
    }

    if(cont < 3)
        return lista;

    pno maior_v = lista, maior_ant = NULL;
    anterior = NULL;
    atual = lista;

    while(atual != NULL){
        if(atual->v > maior_v->v){
            maior_v = atual;
            maior_ant = anterior;
        }
        anterior = atual;
        atual = atual->prox;
    }

    if(maior_v != lista){
        maior_ant->prox = maior_v->prox;
        maior_v->prox = lista;
        lista = maior_v;
    }

    return lista;
}
