#include <stdio.h>
#include <string.h>

#include "banco.h"

// Escreve conteudo do ficheiro binario na consola
// O nome do ficheiro érecebido como parâmetro
void printFile(char *nomeF){
    cliente a;
    FILE *f;

    f = fopen(nomeF, "rb");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro.\n"); return;
    }
    printf("Lista de Clientes:\n");
    while(fread(&a, sizeof(cliente), 1, f) == 1)
        printf("%s - %s - %d - %d\n", a.nome, a.morada, a.conta, a.montante);
    fclose(f);
}

// Escreve tamanho do ficheiro binario e numero de clientes armazenados na consola
// O nome do ficheiro érecebido como parâmetro
void printDados(char *nomeF){
    FILE *f;

    f = fopen(nomeF, "rb");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro.\n"); return;
    }
    fseek(f, 0, SEEK_END);
    printf("\nTamanho do ficheiro: %ld\n", ftell(f));
    printf("Numero de clientes: %ld\n\n", ftell(f) / sizeof(cliente));

    fclose(f);
}

// Corrige morada de um cliente armazenado no ficheiro
// Recebe nome do ficheiro, nome do cliente e nova morada
// Devolve 1 se a correcao for efetuada com sucesso, ou 0, caso contrario
int corrigeMorada(char *nomeF, char *nomeC, char *nMorada){

    FILE *f = fopen(nomeF, "rb+");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro.\n");
        return 0;
    }
    cliente c;
    while(fread(&c, sizeof(cliente), 1, f) == 1) {
        if (strcmp(c.nome, nomeC) == 0) {
            if (strcmp(c.morada, nMorada) != 0) {
                strcpy(c.morada, nMorada);
                fseek(f, -sizeof(cliente), SEEK_CUR);
                fwrite(&c, sizeof(cliente), 1, f);
                fclose(f);
                return 1;
            } else {
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return 0;
}

// Escreve conteudo do ficheiro binario na consola. A informação deve ser listada por ordem alfabética inversa
// O nome do ficheiro érecebido como parâmetro
void printFileInv(char *nomeF) {
    int nrclts;
    cliente c;
    FILE *f;
    f = fopen(nomeF, "rb");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro.\n"); return;
    }

    fseek(f, 0, SEEK_END);
    nrclts = (int)ftell(f)/sizeof(cliente);

    while(nrclts--){
        fseek(f, nrclts*sizeof(cliente), SEEK_SET);
        fread(&c, sizeof(cliente), 1, f);
        printf("%s - %s - %d - %d\n", c.nome, c.morada, c.conta, c.montante);
    }
    fclose(f);
}


// Transfere montante entre 2 clientes
// Recebe nome do ficheiro, identificacaos clientes envolvidos na operacaa e montante a transferir
// Devolve 1 se a transferencia for efetuada com sucesso, ou 0, caso contrario
int transfere(char *nomeF, char *or, char *dest, int valor){
    return 0;
}

// Elimina um cliente do ficheiro, mantendo a ordem alfabetica
// Recebe nome do ficheiro e nome do cliente a eliminar
// Devolve 1 se a eliminação for efetuada com sucesso, ou 0, caso contrario
int eliminaC(char *nomeF, char *nome){
    return 0;
}