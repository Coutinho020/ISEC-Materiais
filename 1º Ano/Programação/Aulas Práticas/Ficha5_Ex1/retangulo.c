#include <stdio.h>
#include "retangulo.h"

// Escreve as coordenadas dos 4 cantos do retangulo recebido como parâmetro
void printRet(ret r){

    printf("(%d, %d)\t", r.canto.x, r.canto.y + r.alt);
    printf("(%d, %d)\n\n", r.canto.x + r.larg, r.canto.y + r.alt);
    printf("(%d, %d)\t",r.canto.x, r.canto.y);
    printf("(%d, %d)\n", r.canto.x + r.larg, r.canto.y);

}

// Inicializa os dados do retangulo referenciado pelo parâmetro recebido.
// O utilizador indica os valores
void initRet(ret* p){

    printf("Indica as coordenadas do canto inferior esquerdo do retangulo(x y): ");
    scanf("%d %d", &p -> canto.x, &p -> canto.y);
    printf("Indica a largura e altura do retangulo (lar, alt): ");
    scanf("%d %d", &p -> larg, &p -> alt);

}

// Devolve a area do retangulo recebido como parâmetro
int areaR(ret r){

    int area = (r.canto.x + r.larg) * (r.canto.y + r.alt);

    return area;
}

// Verifica se o ponto a se encontra dentro do retangulo r
// Devolve 1 se suceder, ou 0, caso contrario
int dentroR(ret r, ponto2D a){

    int x_max = r.canto.x + r.larg;
    int y_max = r.canto.y + r.alt;

    if(a.x > x_max || a.y > y_max || a.x < r.canto.x || a.y < r.canto.y){
        return 0;
    }

    return 1;
}

// Verifica se os 2 retangulos recebidos como parametro se intersetam.
// Devolve 1 se suceder, ou 0, caso contrario
int overlap(ret r1, ret r2){
    return 0;
}