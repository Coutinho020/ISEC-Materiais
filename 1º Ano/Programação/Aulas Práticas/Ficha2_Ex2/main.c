#include <stdio.h>
#define N 3

int Mostra_Matriz(int tab[][3], int nLin){

    int i, j;

    for(i=0;i<nLin;i++){
        for(j=0;j<3;j++){


            printf("[%d] ", tab[i][j]);

        }

        printf("\n");
    }
}

int Preenche_Matriz(int tab[][3], int nLin){

    int i, j;

    for(i=0;i<N;i++){

        printf("Digite um valor inteiro para a linha %d: ", i+1);
        scanf("%d", &tab[i][0]);

        tab[i][1] = tab[i][0] * tab[i][0];
        tab[i][2] = tab[i][0] * tab[i][0] * tab[i][0];

    }
}

int main(){

    int t[N][3];

    Preenche_Matriz(t,N);
    Mostra_Matriz(t, N);

    return 0;
}
