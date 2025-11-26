#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {int mes, ano;} data;
typedef struct emCurso no, *pno;
struct emCurso{
    int id;
    data inicio;
    pno prox;
};
struct completo{
    int id;
    data final;
    int duracao; //duração em meses
};
struct gestor{
    int idG;
    pno lista;
    struct completo *v;
    int total;
};

void imprime_mais_projetos(struct gestor *g, int total){

    int i;

    for(i = 0; i < total; i++){
        int cont = 0;
        pno atual = g[i].lista;

        while(atual != NULL){
            cont++;
            atual = atual->prox;
        }

        if(g[i].total < cont){
            printf("O gestor com o id %d tem mais projetos em curso do que terminados!\n", g[i].idG);
        }
    }
}

int finaliza(struct gestor *a, int tam, int id, data atual){

    int i;

    for(i = 0; i < tam; i++){
        pno atualNo = a[i].lista;
        pno anterior = NULL;
        while(atualno != NULL){
            if(atualNo->id == id){

                int duracao = (atual.ano - a[i].lista->inicio.ano) * 12 + (atual.mes - a[i].lista->inicio.mes);

                struct completo *novoC = realloc(a[i].v, (a[i].total + 1) * sizeof(struct completo));
                if (novoC == NULL){
                    printf("Erro na alocacao de memoria\n");
                    return -1;
                }

                a[i].v = novoC;

                int pos = 0;

                while(a[i].total < pos && a[i].v[pos].id < id){
                    pos++;
                }

                for(int j = a[i].total; j > pos; j--){
                    a[i].v[j] = a[i].v[j - 1];
                }

                a[i].v[pos].id = id;
                a[i].v[pos].duracao = duracao;
                a[i].v[pos].final = atual;
                a[i].total++;

                if(anterior == NULL){
                    a[i].lista = atual->prox;
                }else{
                    anterior->prox = atual->prox;
                }
                free(atualNo);

                return 1;
            }
            anterior = atualNo;
            atualNo = atualNo->prox;
        }
    }
    return 0;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
