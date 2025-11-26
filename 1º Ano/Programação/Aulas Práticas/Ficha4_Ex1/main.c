// Programação 2024-25
// Aula 4 - Matrizes

#include <stdio.h>

// Recebe: Dimensões e endereço de uma matriz de inteiros
// A ordem dos parâmetros é crucial: o número de colunas tem que surgir antes do parâmetro que apresenta a matriz à função.
// A função imprime o conteúdo da matriz na consola
void printMat(int nLin, int nCol, int m[][nCol]){
    int i, j;

    for(i=0; i<nLin; i++){
        for(j=0; j<nCol; j++)
            printf("%d\t", m[i][j]);
        putchar('\n');
    }
}

// Recebe: Dimensões e endereço de uma matriz de inteiros
// Recebe: Endereço de 2 variáveis inteiras onde deve colocar os indices das colunas com menor e maior média
// Escreve na consola as médias dos valores de cada coluna
void calcMediaCol(int nLin, int nCol, int m[][nCol], int* iMin, int* iMax){

    int i, j; float m_maior, m_menor, media[nCol], soma;
    *iMin = 0, *iMax = 0;

    printf("\n");

    for(j = 0; j < nCol; j++) {
        soma = 0;
        media[j] = 0;

        for (i = 0; i < nLin; i++) {

            soma += m[i][j];

        }

        media[j] = soma / nLin;
        printf("Media da coluna %d: %.2f\n", j, media[j]);

        if (j == 0) {

            m_maior = media[j];
            m_menor = media[j];

        } else if (media[j] > m_maior) {

            m_maior = media[j];
            *iMax = j;

        } else if (media[j] < m_menor) {

            m_menor = media[j];
            *iMin = j;

        }
    }

}

// Recebe: Dimensões e endereço de uma matriz de inteiros quadrada
// Efetua a transposicao dos valores na matriz
void tMat(int n, int mat[][n]){

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }

}

int main() {

    int mat1[3][3] = {{1,2,3},{7,8,9},{12,13,14}};
    int mat2[2][5] = {{10,2,13,4,8},{5, 9, 12, 1, 0}};

    int a=-1,b=-1;

    printf("Mat 1:\n");
    printMat(3, 3, mat1);
    printf("\nMat 2:\n");
    printMat(2, 5, mat2);

    calcMediaCol(2, 5, mat2, &a, &b);
    printf("\n\nCol. com menor media: %d\nCol. com maior media: %d\n", a, b);

    tMat(3, mat1);
    printf("\nMat 1 Transposta:\n");
    printMat(3, 3, mat1);
    return 0;
}
