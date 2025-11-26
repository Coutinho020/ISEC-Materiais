#include <stdio.h>
#define n 6

int mostra_posicao(int tab[], int dim){

    int i, posicao = 0, maior = 0;

    for(i = 0; i < dim; i++){

        if(tab[i] > maior){

            maior = tab[i];
            posicao = i;
        }
    }

    printf("Maior elemento: %d\n", maior);
    return posicao;

}

int main() {

    int posicao_m, t[n] = {4, 6, 8, 1, 13, 9};

    posicao_m =  mostra_posicao(t, n);

    printf("Posicao do maior elemento: %d\n", posicao_m);

    return 0;
}
