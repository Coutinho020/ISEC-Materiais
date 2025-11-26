#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {int h, m;} tempo;
typedef struct Voo voo;
struct Voo{
    char codigo[6]; // código do voo
    char destino[4]; // código do destino
    int emTerra; // sim = 1; não = 0;
    tempo t; // hora de partida
};

voo* atualiza_voos(char *Ficheirob, tempo atual, char *cod_d, int *dim){

    FILE *fb = fopen(Ficheirob, "rb+");
    if(fb == NULL){
        printf("Erro ao abrir o ficheiro binario!\n");
        return NULL;
    }

    fseek(fb, 0, SEEK_END);
    long tam = ftell(fb);
    int num_voos = tam / sizeof(voo);

    fseek(fb, 0, SEEK_SET);

    voo *voos = malloc(sizeof(voo) * num_voos);
    if(voos == NULL){
        printf("Erro na alocacao de memoria.\n");
        fclose(fb);
        return NULL;
    }

    fread(voos, sizeof(voo), num_voos, fb);

    for(int i = 0; i < num_voos; i++){
        if((voos[i].t.h < atual.h) || (voos[i].t.h == atual.h && voos[i].t.m < atual.m)){
            voos[i].emTerra = 0;
        }
    }

    fseek(fb, 0, SEEK_SET);
    fwrite(voos, sizeof(voo), num_voos, fb);
    fclose(fb);

    voo *temp = NULL;
    *dim = 0;
    int j = 0;

    for(int i = 0; i < num_voos; i++){
        if(strcmp(voos[i].destino, cod_d) == 0){

            temp = realloc(temp, sizeof(voo) * (j + 1));
            if(temp == NULL){
                printf("Erro na alocacao de memoria.\n");
                free(voos);
                free(temp);
                return NULL;
            }
            temp[j] = voos[i];
            j++;
        }
    }
    *dim = j;
    free(voos);
    return temp;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
