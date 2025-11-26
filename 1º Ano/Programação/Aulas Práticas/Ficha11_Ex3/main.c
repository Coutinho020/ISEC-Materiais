#include <stdio.h>
#include <string.h>

struct paragem{
    char nome[50];
    int minutos;
};

// Recebe nome do ficheiro binário e nomes de 2 paragens
// Verifica se é possivel efetuar a ligação entre as 2 paragens
// Devolve número de minutos que demora a ligar as 2 paragens ou -1, caso seja impossivel
int liga(char *nome, char *or, char *dest){

    return -1;
}

// Recebe nome do ficheiro binário e nome de paragem
// Verifica se paragem faz parte do percurso ou não. Devolve 1(Sim) ou 0 (Não)
int existeParagem(char *nomeF, char *paragem){
    return 0;
}

// Recebe nome do ficheiro binário
// Escreve na consola o nome da origem e do destino do percurso
void orDest(char *nomeF){

    FILE *f;
    struct paragem origem, destino;

    f = fopen(nomeF, "rb");
    if(f == NULL){
        printf("Erro ao abrir ficheiro.\n");
        return;
    }

    // Ler a primeira paragem (origem)
    if(fread(&origem, sizeof(struct paragem), 1, f) != 1){
        printf("Ficheiro vazio ou erro de leitura.\n");
        fclose(f);
        return;
    }

    // Procurar a última paragem (destino)
    while(fread(&destino, sizeof(struct paragem), 1, f) == 1){
        // Vai atualizando até chegar ao fim
    }

    printf("Origem: %s\n", origem.nome);
    printf("Destino: %s\n", destino.nome);

    fclose(f);

}

// Recebe nome do ficheiro binário
// Escreve na consola as varias paragens do percurso armazenado
void mostraPercurso(char *nomeF) {
    FILE *f;
    struct paragem p;

    f = fopen(nomeF, "rb");
    if(f == NULL) {
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    while(fread(&p, sizeof(struct paragem), 1, f) == 1)
        printf("%s: %d\n", p.nome, p.minutos);

    fclose(f);
}

int main() {

    mostraPercurso("cp_ex3.dat");

    orDest("cp_ex3.dat");

    printf("\nParagem: %d\n", existeParagem("cp_ex3.dat", "Porto"));

    printf("\nLigacao: %d\n", liga("cp_ex3.dat", "Coimbra", "Porto"));


    return 0;
}
