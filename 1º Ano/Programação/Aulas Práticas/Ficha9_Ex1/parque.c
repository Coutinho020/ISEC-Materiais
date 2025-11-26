#include <stdlib.h>
#include <stdio.h>

#include "parque.h"


// Liberta todo o espaco ocupado pela estrutura dinamica

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
// Cria e devolve uma estrutura dinamica exemplo para teste das funções deste exercicio
// A informação criada é igual ao exemplo ilustrado na ficha pratica 9

pCliente criaExemploED(){
    int totC = 3, i, j, k=-1;
    cliente a[] = {{13, 2, NULL, NULL},{17,1,NULL,NULL},{22,3,NULL,NULL}};
    acesso b[] = {{{10,20},{11,52},NULL}, {{14,30},{17,2},NULL}, {{10,50},{-1,-1},NULL},
                  {{9,11},{9,12},NULL},{{10,5},{12,0},NULL},{{14,33},{-1,-1},NULL}};

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


// Recebe ponteiro para o inicio da estrutura dinamica
// Escreve toda a informação armazenada (clientes e respetivos acessos)
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


// Recebe ponteiro para o inicio da estrutura dinamica
// Devolve numero de clientes que se encontram no parque (têm uma utilização em aberto)
int dentroParque(pCliente p){

    pCliente auxC = p;
    pAcesso auxA;

    int cont = 0;

    while(auxC != NULL){
        auxA = auxC->lista;
        while(auxA != NULL){
            if(auxA->out.h == -1){
                cont++;
            }
            auxA = auxA->prox;
        }
        auxC = auxC->prox;
    }
    return cont;
}


// Recebe ponteiro para o inicio da estrutura dinamica e hora
// Devolve numero de clientes que estavam dentro do parque na hora x
int dentroParqueHora(pCliente p, hora x){

    pCliente auxC = p;
    pAcesso auxA;

    int cont=0;

    while(auxC != NULL){
        auxA = auxC->lista;
        while(auxA != NULL){
            if(((auxA->in.h == x.h && auxA->in.m <= x.m) || (auxA->in.h < x.h)) &&
               ((auxA->out.h > x.h) || (auxA->out.h == x.h && auxA->out.m >= x.m) || (auxA->out.h == -1))){
                cont ++;
            }
            auxA = auxA->prox;
        }
        auxC = auxC->prox;
    }
    return cont;
}

// Recebe ponteiro para o inicio da estrutura dinamica e endereço de variável inteira
// Devolve id do cliente que passou mais minutos no parque e coloca esse número de minutos na variável referenciada pelo segundo parametro
int maisMinutos(pCliente p, int *m){

    *m = 0;
    pAcesso auxA;
    pCliente auxC = p;

    int minutos, id_max;

    while(auxC != NULL){
        auxA = p->lista;
        minutos = 0;
        while(auxA != NULL){
            if(auxA->out.h != -1) {
                minutos += ((auxA->out.h - auxA->in.h) * 60) + auxA->out.m - auxA->in.m;
            }
            auxA = auxA->prox;
        }
        if(minutos > *m){
            *m = minutos;
            id_max = auxC->id;
        }
        auxC=auxC->prox;
    }
    return id_max;
}

pCliente eliminaCliente(pCliente p, int id){

    pCliente auxC = p, anteriorC = NULL;
    pAcesso auxA, temp;

        while(auxC != NULL && auxC->id != id){
            anteriorC = auxC;
            auxC= auxC->prox;
        }

        if(auxC->id != id){
            printf("\nO Cliente com o id %d, nao teve acessos hoje!\n");
            return p;
        }else{
            auxA = auxC->lista;
            while(auxA != NULL){
                auxC->lista = auxA->prox;
                temp = auxA;
                auxA = auxA->prox;
                free(temp);
            }
        }

        if(anteriorC == NULL){
            p = auxC->prox;
        }else{
            anteriorC->prox = auxC->prox;
        }
        free(auxC);
        return p;
    }


pCliente elimina_sessoes_abertas(pCliente p) {

    pCliente auxC = p, anteriorC = NULL, tempC;
    pAcesso auxA, anteriorA = NULL;

    while(auxC != NULL) {
        auxA = auxC->lista;
        anteriorA = NULL;
            while(auxA != NULL) {
                if (auxA->out.h == -1) {
                    if (anteriorA == NULL) {
                         auxC->lista = auxA->prox;
                    } else {
                        anteriorA->prox = auxA->prox;
                    }
                    free(auxA);
                    auxC->contador--;
                }else{
                     anteriorA = auxA;
                     auxA = auxA->prox;
                 }
         }

        if (auxC->contador == 0) {
            if (anteriorC == NULL){
                p = auxC->prox;
            } else {
                anteriorC->prox = auxC->prox;
            }
            tempC = auxC;
            auxC = auxC->prox;
            free(tempC);
        }else{
            anteriorC = auxC;
            auxC = auxC->prox;
        }
    }
    return p;
}

// Recebe ponteiro para o inicio da estrutura dinamica, id de um cliente e hora de ativação da cancela
// Devolve ponteiro para inicio da estrutura dinamica depois de atualizar o registo do cliente com este novo acesso
pCliente acessoParque(pCliente p, int id, hora x){

    pAcesso auxA, anteriorA = NULL, novoA;
    pCliente auxC = p, anteriorC = NULL, novoC;

    while(auxC != NULL && auxC->id < id){
        anteriorC = auxC;
        auxC = auxC->prox;
    }

    if(auxC == NULL || auxC->id > id){

        novoC = malloc(sizeof(cliente));
        if(novoC == NULL){
            printf("\nErro na alocacao de memoria!\n");
            return p;
        }
        novoC->id = id;
        novoC->contador = 0;
        novoC->lista =NULL;
        novoC->prox = NULL;

        if(anteriorC == NULL){
            novoC->prox = p;
            p = novoC;
        }else{
            anteriorC->prox = novoC;
            novoC->prox = auxC;
        }
        auxC = novoC;
    }

    auxA = auxC->lista;
    anteriorA = NULL;

    while(auxA != NULL) {
        if (auxA->out.h == -1){
            auxA->out = x;
            return p;
        }
        anteriorA = auxA;
        auxA = auxA->prox;
    }

    novoA = malloc(sizeof(novoA));
    novoA->in = x;
    novoA->out.h = novoA->out.m = -1;
    novoA->prox = NULL;

    if(anteriorA == NULL){
        auxC->lista = novoA;
    }else{
        anteriorA->prox = novoA;
    }
    auxC->contador++;
    return p;
}
