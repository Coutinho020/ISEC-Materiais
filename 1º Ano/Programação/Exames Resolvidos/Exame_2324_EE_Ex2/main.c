#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {int mes, ano;} data;
typedef struct gestor no, *pno;
struct gestor{
    int idG;
    struct emCurso *v1;
    struct completo *v2;
    int totV1, totV2;
    pno prox;
};
struct emCurso{
    int id;
    data inicio;
};
struct completo{
    int id;
    data final;
    int duracao;
};

void imprime_informacoes(pno lista, int id_p){

    pno atual = lista;

    while(atual != NULL){
        for(int i = 0; i < lista->totV1; i++){
            if(lista->v1[i].id == id_p){
                printf("Projeto em Curso, ID do gestor -> %d\n", id_p);
                return;
            }
        }

        for(int j = 0; j < lista->totV2; j++){
            if(lista->v2[j].id == id_p){
                printf("Projeto Concluido, ID do gestor -> %d\n", id_p);
                return;
            }
        }
        atual = atual->prox;
    }
    printf("Inexistente\n");
}

pno elimina_gestor (pno lista){

    pno atual = lista;
    pno anterior = NULL;

    while(atual != NULL){
        if(atual->totV1 == 0){
            pno temp = atual;

            if(anterior == NULL){
                lista = atual->prox;
                atual = atual->prox;
            }else{
                anterior->prox = atual->prox;
                atual = atual->prox;
            }
            free(temp->v1);
            free(temp->v2);
            free(temp);
        }else {
            anterior = atual;
            atual = atual->prox;
        }
    }
    return lista;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
