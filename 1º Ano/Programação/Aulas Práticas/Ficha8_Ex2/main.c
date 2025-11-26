#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa no, *pno;

struct pessoa{
    char nome[100];
    int id;
    float peso, altura, imc;
    pno prox;
};


// Função auxiliar para obter dados do utilizador e prencher um novo nó a inserir na lista
// Recebe endereço do nó a preencher
void getDados(pno p){
    printf("Nome: ");
    scanf(" %[^\n]", p->nome);
    printf("ID: ");
    scanf("%d", &(p->id));
    printf("Peso (Kg) e Altura (Metros): ");
    scanf("%f %f", &(p->peso), &(p->altura));
    p->imc = p->peso / (p->altura * p->altura);
    p->prox = NULL;
}

// Função para adicionar um novo nó à lista
// Recebe ponteiro de lista e devolve ponteiro de lista depois da inserção
// Esta função não está de acordo com o pedido no enunciado (2b) e tem que ser corrigida em 2 pontos:
// 1. Insere o novo nó no início da liste e não no final
// 2. Não valida se o ID é único. Esta validação poderá ser feita diretamente na função GetDados(), mas,
// para isso, terá que receber o ponteiro de lista como parâmetro adicional
pno addLista(pno lista) {

    pno novo, aux;
    int idDuplicado;

    do {
        novo = malloc(sizeof(no));
        if (novo == NULL) {
            printf("Erro na alocação de memória.\n");
            return lista;
        }

        getDados(novo);
        idDuplicado = 0;
        aux = lista;

        while (aux != NULL) {
            if (aux->id == novo->id) {
                printf("ID ja existe! Insira novamente os dados.\n");
                idDuplicado = 1;
                free(novo);

            }
            aux = aux->prox;
        }

    } while (idDuplicado);

    if(lista == NULL){
        return novo;
    }else{
        aux = lista;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
        return lista;
    }
}

// Função que mostra o conteúdo da lista
// Recebe ponteiro de lista como parâmetro
void mostraLista(pno lista){

    if(lista == NULL){
        printf("A lista esta vazia!\n");
        return;
    }

    while (lista != NULL){
        printf("%d - %s\n", lista->id, lista->nome);
        printf("P: %.1f\tA: %.1f\tIMC: %.2f\n\n", lista->peso, lista->altura, lista->imc);
        lista = lista->prox;
    }
}

// Função para atualizar o peso de uma das pessoas
// Recebe ponteiro de lista, id da pessoa a atualizar e novo peso
// Deve tambem ser atualizado o imc
void atualizaPeso(pno lista, int id, float novoPeso){

}

// Função para eliminar uma pessoa da lista
// Recebe ponteiro de lista e id da pessoa a eliminar
// Devolve ponteiro de lista depois da eliminação
pno elimina(pno lista, int id){

    pno atual, anterior;
    atual = lista;

    while(atual != NULL && atual->id != id){
        anterior = atual;
        atual = atual ->prox;
    }
    if(atual == NULL)
        return lista;
    if(anterior == NULL)
        lista = atual->prox;
    else
        anterior->prox = atual->prox;
    free(atual);
    return lista;
}

int main(){
    pno lista = NULL;   // Criação do ponteiro de lista
    int i;

    for(i=0; i<3; i++)
        lista = addLista(lista);
    mostraLista(lista);

    //atualizaPeso(lista, 123, 78.5);

    //lista = elimina(lista, 456);
    //mostraLista(lista);

    free(lista);

    return 0;
}
