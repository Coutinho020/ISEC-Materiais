#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Artigo artigo;
typedef struct Data data;
struct Data{ int hora, minuto, dia, mes, ano;};
struct Artigo{
 int cp; // Código numérico único do artigo
 int np; // Quantidade do artigo existente em stock
 float preco; // Preço unitário (em euros)
 data venda; // Data em que foi realizada a última venda
};

int atualiza_ficheiro(char *Ficheirob, char *Ficheirot, data d){

    FILE *fb = fopen(Ficheirob, "rb+");
    if(fb == NULL){
        printf("Erro ao abrir o ficheiro binario\n");
        return -1;
    }

    FILE *ft = fopen(Ficheirot, "r");
    if(ft == NULL){
        printf("Erro ao abrir o ficheiro texto\n");
        fclose(fb);
        return -1;
    }

    int M;
    fread(&M, sizeof(int), 1, fb);

    artigo *artigos = malloc(sizeof(artigo) * M);
    if(artigos == NULL){
        printf("Erro na alocacao de memoria\n");
        fclose(fb);
        fclose(ft);
        return -1;
    }

    fread(artigos, sizeof(artigo), M, fb);

    int codigo, quantidade;
    float total = 0.0;
    int vendidos;

    while(fscanf(ft, "%d %d", &codigo, &quantidade) == 2){
        for(int i = 0; i < M; i++){
            if(artigos[i].cp == codigo){
                if(quantidade <= artigos[i].np){
                    vendidos = quantidade;
                }else{
                    vendidos = artigos[i].np;
                }

                total += (artigos[i].preco * vendidos);
                artigos[i].np -= quantidade;
                artigos[i].venda = d;
            }
        }
    }

    fclose(ft);
    fseek(fb, 0, SEEK_SET);
    fwrite(&M, sizeof(int), 1, fb);
    fwrite(artigos, sizeof(artigo), M, fb);
    fclose(fb);
    free(artigos);

    return total;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
