#include <stdio.h>
#include <stdbool.h>
#define N 3

// Função para verificar se um número é primo
int ehPrimo(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0){

            printf("Nao e um numero primo!!!!!\n");
            return 0;
        }
    }
    return 1;
}

// Função para verificar se um número já está presente na matriz
int existeNaMatriz(int matriz[][3], int linhas, int num) {
    for (int i = 0; i < linhas; i++) {
        if (matriz[i][0] == num){

            printf("Numero Repetido!!!\n");
            return 1;
        }
    }
    return 0;
}

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

        do {

            printf("Digite um valor inteiro para a linha %d: ", i + 1);
            scanf("%d", &tab[i][0]);

        }while(tab[i][0] < 1 || tab[i][0] > 100 || !ehPrimo(tab[i][0]) || existeNaMatriz(tab, i, tab[i][0]));

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