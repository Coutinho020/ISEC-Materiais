#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dados item;
struct dados{
    int id; // Identificador numérico único
    char nome[100]; // Nome do item
    int qtd; // Quantidade em stock
    int minstock; // Quantidade mínima para gerar alerta de stock
};

int atualiza_ingredientes(char *Ficheirob, char *Ficheirot){

    FILE *fb = fopen(Ficheirob, "rb+");
    FILE *ft = fopen(Ficheirot, "r");

    if(fb == NULL || ft == NULL){
        fclose(fb);
        fclose(ft);
        return 0;
    }

    int id_item, quantidade;
    char nome_item[100], comentario[100];

    while(fscanf(ft, " %d : %99[^:] : %d : %99[^\n]\n", &id_item, nome_item, &quantidade, comentario) == 4){

        long pos = (id_item - 1) * sizeof(item);
        fseek(fb, pos, SEEK_SET);

        item ingrediente;
        fread(&ingrediente, sizeof(item), 1, fb);
        ingrediente.qtd -= quantidade;

        fseek(fb, pos, SEEK_SET);

        fwrite(&ingrediente, sizeof(item), 1, fb);

        if(ingrediente.qtd < ingrediente.minstock){
            printf("O ingrediente %s com ID %d tem stock abaixo do minimo\n", ingrediente.nome, ingrediente.id);
        }
    }

    fclose(fb);
    fclose(ft);
    return 1;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
