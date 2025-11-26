#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct a autor;
typedef struct b livro;
struct a{
    char nome[100]; // Nome do autor
    int idA; // Identificador numérico do autor
    int nLivros; // Número de títulos no catálogo da livraria
};
struct b{
    char titulo[100], isbn[20]; // Título e isbn do livro
    int idA; // Identificador do autor
    float preco; // Preço do livro
};

int pesquisa_autores (char *Ficheirob, char *Ficheirot, int id){

    FILE *ft, *fb = fopen(Ficheirob, "rb+");
    if(fb == NULL){
        return 0;
    }

    int X, Y, i, j;

    fread(&X, sizeof(int), 1, fb);
    autor *autores = malloc(sizeof(autor) * X);
    fread(autores, sizeof(autor), X, fb);

    ft = fopen(Ficheirot, "w");
    if(ft == NULL){
        fclose(fb);
        free(autores);
        return 0;
    }

    fread(&Y, sizeof(int), 1, fb);
    livro * livros = malloc(sizeof(livro) * Y);
    fread(livros, sizeof(livro), Y, fb);

    // Parte i: verificar qual autor tem mais livros

    int max_livros = -1, id_max = -1, cont = 0;

    for(i = 0; i < X; i++){
        if(autores[i].nLivros > max_livros){
            max_livros = autores[i].nLivros;
            id_max = autores[i].idA;
            cont = 1;
        } else if (autores[i].nLivros == max_livros){
            cont++;
        }
    }

    // Se apenas um autor tiver o máximo de livros, atualizar preços

    if(cont == 1){
        for(j = 0; j < Y; j++){
            if(livros[j].idA == id_max){
                livros[j].preco *= 1.1f;
            }
        }
        // Regravar livros no ficheiro
        fseek(fb, sizeof(int) + sizeof(autor) * X + sizeof(int), SEEK_SET);
        fwrite(livros, sizeof(livro), Y, fb);
    }

    // Parte ii: criar ficheiro de texto com os livros do autor com id = idAutorFiltro

    int autor_encontrado = 0;
    char nomeAutor[20];

    for(i = 0; i < X; i++){
        if(autores[i].idA == id){
            autor_encontrado = 1;
            strcpy(nomeAutor, autores[i].nome);
        }
    }

    if(autor_encontrado != 1){
        fprintf(ft, "Autor Inexistente\n");
    }else{
        for(i = 0; i < Y; i++){
            if(livros[i].idA == id){
                fprintf(ft, "%s - %s, %s\n", livros[i].isbn, livros[i].titulo, nomeAutor);
            }
        }
    }
    fclose(fb);
    fclose(ft);
    free(autores);
    free(livros);
    return 1;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
