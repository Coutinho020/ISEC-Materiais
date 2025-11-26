
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parque.h"

// Nome: Diogo Coutinho Amor Antunes
// Número: 2018016615


void libertaTudo(pCliente p){
    pCliente auxC;
    pAcesso auxA;

    while(p != NULL){
        while(p->lista != NULL){
            auxA = p->lista;
            p->lista = p->lista->prox;
            free(auxA);
        }
        auxC = p;
        p = p->prox;
        free(auxC);
    }
}

pCliente criaExemploED(cliente a[], acesso b[], int totC){
    int i, j, k=-1;

    pCliente lista = NULL, novoC;
    pAcesso novoA;

    for(i=0; i<totC; i++){
        k+=a[i].contador;
    }
    for(i=totC-1; i>=0; i--){
        novoC = malloc(sizeof(cliente));
        if(novoC == NULL){
            libertaTudo(lista);
            return NULL;
        }
        *novoC = a[i];
        novoC->prox = lista;
        lista = novoC;
        for(j=0; j<novoC->contador; j++){
            novoA = malloc(sizeof(acesso));
            if(novoA == NULL){
                libertaTudo(lista);
                return NULL;
            }
            *novoA = b[k--];
            novoA->prox = novoC->lista;
            novoC->lista = novoA;
        }
    }
    return lista;
}

void mostraTudo(pCliente p){
    pAcesso auxA;

    while(p != NULL){
        printf("\nUtilizador com id %d efetuou %d acessos\n", p->id, p->contador);
        auxA = p->lista;
        while(auxA != NULL){
            printf("Entrou as %2.2d:%2.2d. ", auxA->in.h, auxA->in.m);
            if(auxA->out.h == -1)
                printf("Ainda nao saiu do parque\n");
            else
                printf("Saiu as %2.2d:%2.2d\n", auxA->out.h, auxA->out.m);
            auxA = auxA->prox;
        }
        p = p->prox;
    }
}

pCliente desafio4(pCliente lista, hora *x, int id, int *valor){

    pCliente aux = lista, anteriorC = NULL;
    pAcesso auxA, anteriorA;
    int encontrou_cliente = 0;
    int minutos_entrada, minutos_saida, duracao;

    // 1. Determinar a hora de entrada do primeiro cliente
    x->h = -1;  // Inicializar com -1:-1
    x->m = -1;

    while (aux != NULL) {
        auxA = aux->lista;
        while (auxA != NULL) {
            // Se x ainda for o valor inicial ou a hora de entrada do corrente_acesso for menor que a menor até agora
            if (x->h == -1 || (auxA->in.h < x->h || (auxA->in.h == x->h && auxA->in.m < x->m))) {
                x->h = auxA->in.h;
                x->m = auxA->in.m;
            }
            auxA = auxA->prox;
        }
        aux = aux->prox;
    }

    // 2. Calcular o valor a pagar pelo cliente com o ID especificado
    *valor = 0; // Inicializa o valor a pagar
    aux = lista; // Reset atual
    while (aux != NULL) {
        if (aux->id == id) {
            encontrou_cliente = 1;
            auxA = aux->lista;
            while (auxA != NULL) {
                if (auxA->out.h != -1) { // Apenas utilizações completas
                    minutos_entrada = auxA->in.h * 60 + auxA->in.m;
                    minutos_saida = auxA->out.h * 60 + auxA->out.m;
                    duracao = minutos_saida - minutos_entrada;
                    *valor += duracao * 10; // 10 cêntimos por minuto
                }
                auxA = auxA->prox;
            }
            break; // Importante: Sai do loop após encontrar o cliente
        }
        aux = aux->prox;
    }

    // 3. Remover utilizações completas e, possivelmente, o cliente
    if (encontrou_cliente) { // Só faz esta parte se encontrou o cliente
        aux = lista; // Reset atual para usar no processo de remoção
        anteriorC = NULL;

        while (aux != NULL) {
            if (aux->id == id) {
                auxA = aux->lista;
                anteriorA = NULL;
                while (auxA != NULL) {
                    if (auxA->out.h != -1) { // Remover utilizações completas
                        pAcesso temp = auxA;
                        if (anteriorA == NULL) {
                            aux->lista = auxA->prox;
                        } else {
                            anteriorA->prox = auxA->prox;
                        }
                        auxA = auxA->prox;
                        free(temp);
                        aux->contador--; // Decrementa o contador de utilizações
                    } else {
                        anteriorA = auxA;
                        auxA = auxA->prox;
                    }
                }

                // Verificar se o cliente deve ser removido
                if (aux->contador == 0) {
                    if (anteriorC == NULL) {
                        lista = aux->prox;
                    } else {
                        anteriorC->prox = aux->prox;
                    }
                    pCliente temp = aux;
                    aux = aux->prox;
                    free(temp);
                } else {
                    aux = aux->prox;
                }
                break;
            }   else {
                anteriorC = aux;
                aux = aux->prox;
            }
        }
    }

    return lista;
}
