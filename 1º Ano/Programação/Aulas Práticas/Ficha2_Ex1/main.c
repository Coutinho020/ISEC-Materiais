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

int main() {

    int t[N][3] = {{1,2,3}, {4,5,6}, {7,8,9}};

    Mostra_Matriz(t,N);

    return 0;
}
