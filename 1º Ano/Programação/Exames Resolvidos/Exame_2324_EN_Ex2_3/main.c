#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dadosUc uc, *pUc;
typedef struct dadosSala sala, *pSala;
typedef struct {int dia, mes, ano;} data;
struct dadosUc{
    char refUc[100]; // Nome da Unidade Curricular
    data dataEx; // Data do exame
    pSala lista; // Ponteiro para a lista de salas
};
struct dadosSala{
    char refSala[100]; // Nome da sala
    int capacidade; // Capacidade de sala
    pSala prox;
};

void imprime_salas(pUc p, int total, char *sala) {

    int i, encontrou = 0;

    for (i = 0; i < total; i++) {
        pSala atual = p[i].lista;
        while (atual != NULL) {
            if (strcmp(atual->refSala, sala) == 0) {
                printf("UC com exame na sala %s -> %s\n", sala, p[i].refUc);
                encontrou = 1;
            }
            atual = atual->prox;
        }
    }
    if(encontrou == 0){
        printf("Nenhuma unidade curricular tem o exame na sala '%s'.\n", sala);
    }
}

pUc elimina(pUc v, int *nUcs, data d){

    int i, cont = 0;

    for(i = 0; i < *nUcs; i++){
        if((v[i].dataEx.ano < d.ano) ||
                (v[i].dataEx.ano == d.ano && v[i].dataEx.mes < d.mes) ||
                (v[i].dataEx.ano == d.ano && v[i].dataEx.mes == d.mes && v[i].dataEx.dia < d.dia)){

            pSala atual = v[i].lista;
            pSala anterior = NULL;
            while(atual != NULL){
             anterior = atual;
             atual = atual->prox;
             free(anterior);
            }

            cont++;
        }
    }

    if((*nUcs) - cont == 0){
        free(v);
        return NULL;
    }

    int novas = *nUcs - cont;

    pUc novo = malloc(sizeof(uc) * novas);
    if(novo == NULL){
        return v;
    }

    for(int j=0; j < novas; j++){
        novo[j] = v[j + cont];
    }

    free(v);
    *nUcs = novas;
    return novo;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
