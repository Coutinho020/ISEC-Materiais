#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct local no, *pno;
struct local{
    char nome[50];
    pno prox;
};


void mostra_info(pno p){
    if(p == NULL)
    {
        printf("Lista Vazia.\n");
        return;
    }
    else
        while(p != NULL)
        {
            printf("%s\n", p->nome);
            p = p->prox;
        }
}

/* Inserir um novo elemento numa lista ligada */
/*Tr�s etapas:
1. Arranjar espa�o em mem�ria para o novo n�.
2. Preencher o novo n� com informa��o.
3. Inserir o novo n� na lista.*/

/* Inserir um novo elemento no INICIO duma lista ligada */
pno addNo_1(pno lista, char *st){
    pno novo;

// 1. Arranjar espa�o em mem�ria para o novo n�.
    novo = malloc(sizeof(no));
    if(novo == NULL){
        printf("Erro na alocacao de memoria\n");
        return lista;
    }

// 2. Preencher o novo n� com informa��o.
    strcpy(novo->nome, st);
//3. Inserir o novo n� na lista.
//   O caso em que a lista est� vazia insere-se no caso geral
    novo->prox = lista;
    return novo; // novo passa a ser o novo "cabe�a da lista"
}

// -------------------------------------------------------------
/* Inserir um novo elemento no FINAL duma lista ligada */
pno addNo_2(pno lista, char *st){
    pno novo, aux=lista;
    novo = malloc(sizeof(no));
    if(novo == NULL)
        return lista;
    strcpy(novo->nome, st);
    novo->prox = NULL;
    if(lista == NULL)  //Caso particular de lista vazia
        lista = novo;
    else{
        while(aux->prox != NULL)  //Caso Geral
            aux = aux->prox;
        aux->prox = novo;
    }
    return lista;
}
// -------------------------------------------------
/* Inserir um novo elemento � frente do 1� elemento da lista ligada
   (novo elemento fica na 2a posi��o) */
pno addNo_3(pno lista, char *st){
    pno novo;
    novo = malloc(sizeof(no));
    if(novo == NULL)
        return lista;
    strcpy(novo->nome, st);

    if(lista == NULL) {
        novo->prox = lista;
        lista = novo;
    }
    else {
        novo->prox = lista->prox;
        lista->prox = novo;
    }
    return lista;
}


int main()
{
    pno lista = NULL;
    mostra_info(lista);

    printf("\nInserir um novo elemento no INICIO da lista:\n");
    lista = addNo_1(lista, "AAA");
    lista = addNo_1(lista, "BBB");
    lista = addNo_1(lista, "CCC");
    mostra_info(lista);

    free(lista);  lista = NULL;

    printf("\nInserir um novo elemento no FINAL da lista:\n");
    lista = addNo_2(lista, "AAA");
    lista = addNo_2(lista, "BBB");
    lista = addNo_2(lista, "CCC");
    mostra_info(lista);

    free(lista);  lista = NULL;

    printf("\nInserir um novo elemento na 2a posi��o da lista:\n");
    lista = addNo_3(lista, "AAA");
    lista = addNo_3(lista, "BBB");
    lista = addNo_3(lista, "CCC");
    lista = addNo_3(lista, "DDD");
    lista = addNo_3(lista, "EEE");
    mostra_info(lista);

    free(lista);  lista = NULL;

    printf("\n MIX:\n");
    lista = addNo_3(lista, "AAA");
    lista = addNo_1(lista, "BBB");
    lista = addNo_1(lista, "CCC");
    lista = addNo_2(lista, "DDD");
    lista = addNo_3(lista, "EEE");
    mostra_info(lista);

    free(lista);
}