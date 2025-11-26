#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct a autor;
struct a{
    char nome[100]; // Nome do autor
    int idA; // Identificador numérico do autor
    int nLivros; // Número de títulos no catálogo da livraria
};

int atualiza_ficheiros(char *Ficheirob, char *FicheiroT){

    FILE *ft = fopen(FicheiroT, "r");
    if(ft == NULL){
        printf("Erro ao abrir o ficheiro texto\n");
        return 0;
    }

    FILE *fb = fopen(Ficheirob, "rb+");
    if(fb == NULL){
        printf("Erro ao abrir o ficheiro binario\n");
        fclose(ft);
        return 0;
    }

    int total_autores = 0;

    fread(&total_autores, sizeof(int), 1, fb);
    autor *autores = malloc(sizeof(autor) * total_autores);
    if(autores == NULL){
        printf("Erro na alocacao de memoria\n");
        fclose(ft);
        fclose(fb);
        return 0;
    }

    fread(autores, sizeof(autor), total_autores, fb);

    char titulo[100];
    int idAutor;
    float preco;

    while(fscanf(" %99[^#] %d # %f ", titulo, &idAutor, &preco) == 3){
        for(int i = 0; i < total_autores; i++){
            if(autores[i].idA == idAutor) {
                autores[i].nLivros++;
            }
        }
    }

    fclose(ft);
    ft = fopen(FicheiroT, "r");
    if(ft == NULL){
        printf("Erro na abertura do ficheiro texto\n");
        fclose(fb);
        free(autores);
        return 0;
    }

    for(int i = 0; i < total_autores; i++){
        if(autores[i].nLivros > 0){
            int cont = 0;
            float soma = 0.0;

            fseek(ft, 0, SEEK_SET);
            while(fscanf(" %99[^#] # %d # %f ", titulo, &idAutor, &preco) == 3){
             if(autores[i].idA == idAutor){
                 soma += preco;
                 cont++;
             }
            }
            float media = soma / cont;
            printf("O preco medio dos livros do autor %s e %.2f euros.\n", autores[i].nome, media);
        }else{
            printf("Autor %s nao tem livros registados.\n", autores[i].nome);
        }
    }

    fclose(ft);
    fclose(fb);
    free(autores);
    return 1;

}

int main() {
    printf("Hello, World!\n");
    return 0;
}
