#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct projeto proj, *pproj;
typedef struct pessoa gestor, *pgest;
struct pessoa{
    int id; // Identificador único do gestor
    char nome[100]; // Nome do gestor
    int total; // Número de projetos que está a gerir
};
struct projeto{
    int id; // Identificador único do projeto
    struct {int dia, mes, ano;} inicio; // Data de início do projeto
    pgest p; // Ponteiro para o gestor deste projeto
    pproj prox;
};

void imprime_datas (int id_g, pproj lista, pgest gestores, int n_gestores){

    int i;
    pgest gestor_encontrado = NULL;

    for(i = 0; i < n_gestores; i++){
        if(gestores[i].id = id_g){
            gestor_encontrado = &gestores[i];
        }
    }

    if(gestor_encontrado == NULL || gestor_encontrado->total < 2){
        printf("Nao aplicavel\n");
        return;
    }

    // Inicializar variáveis para data mais antiga e mais recente
    int primeiro = 1;
    int dia_min, mes_min, ano_min;
    int dia_max, mes_max, ano_max;

    pproj atual = lista;
    while(atual != NULL){
        if(atual != NULL && atual->p->id == id_g){
            int d = atual->inicio.dia;
            int m = atual->inicio.mes;
            int a = atual->inicio.ano;

            if(primeiro == 1){
                dia_min = dia_max = d;
                mes_min = mes_max = m;
                ano_min = ano_max = a;
                primeiro = 0;
            }else{
                // Comparar para data mais antiga
                if (a < ano_min || (a == ano_min && m < mes_min) || (a == ano_min && m == mes_min && d < dia_min)) {
                    dia_min = d;
                    mes_min = m;
                    ano_min = a;
                }
                // Comparar para data mais recente
                if (a > ano_max || (a == ano_max && m > mes_max) || (a == ano_max && m == mes_max && d > dia_max)) {
                    dia_max = d;
                    mes_max = m;
                    ano_max = a;
                }
            }
        }
        atual = atual->prox;
    }

    // Apenas imprime: sabemos que há pelo menos 2 projetos
    printf("Projeto mais antigo: %02d/%02d/%04d\n", dia_min, mes_min, ano_min);
    printf("Projeto mais recente: %02d/%02d/%04d\n", dia_max, mes_max, ano_max);
}

pgest eliminaGestor(int id_gestor, pproj lista, pgest gestores, int *total){

    int i, i_eliminar = -1;

    for(i = 0; i < *total; i++){
        if(gestores[i].id = id_gestor){
            i_eliminar = i;
        }
    }

    if(i_eliminar == -1){
        return gestores;
    }

    int i_destino = -1;

    for(i = 0; i < *total; i++){
        if(i != i_eliminar){
            if(i_destino == -1 ||
            gestores[i].total < gestores[i_destino].total ||
            (gestores[i].total == gestores[i_destino].total && gestores[i].id < gestores[i_destino].id)){
                i_destino = i;
            }
        }
    }
    pproj atual = lista;

    while(atual != NULL){
        if(atual->p->id == id_gestor){
            atual->p = &gestores[i_destino];
            gestores[i_destino].total++;
            gestores[id_gestor].total--;
        }
        atual = atual->prox;
    }

    gestor *novo = malloc(sizeof(gestor) * (*total - 1));
    if(novo == NULL){
        printf("Erro na alocacao de memoria");
        return gestores;
    }

    int k = 0;
    for(i = 0; i < *total; i++){
        if(i != i_eliminar){
            novo[k] = gestores[i];
            k++;
        }
    }
    free(gestores);
    (*total)++;
    return novo;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
