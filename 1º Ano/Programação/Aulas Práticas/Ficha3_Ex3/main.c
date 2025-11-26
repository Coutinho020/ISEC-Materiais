// Programação 2024/25
// Aula Prática 3 - Ponteiros e Endereços: Comunicação entre funções e manipulação de tabelas

#include <stdio.h>

int verifica_par_impar(int tab[], int n){

    int i, npares = 0, nimpar = 0, maior = 0, posicao = 0;

    for(i=0; i < n; i++){

        if(tab[i]%2 == 0){

            npares++;

        }else if(tab[i]%2 != 0){}

        nimpar++;

    }

    for(i=0; i<n; i++){

        if(tab[i] > maior){

            maior = tab[i];
            posicao = i;

        }

    }

    printf("Numeros pares: %d\n", npares);
    printf("Numeros impares: %d\n", nimpar);
    printf("Maior: %d\n", maior);
    printf("Posicao do maior elemento: %d\n", posicao);

}

// Exercicio 3
// Recebe: Endereços/ponteiros para 3 variáveis do tipo float
// Deve efetuar a rotação de valores entre essas variáveis
void rotacao(float *p1, float *p2, float *p3){

    float temp;
    temp = *p3;
    *p3 = *p2;
    *p2 = *p1;
    *p1 = temp;

}

// Exercicio 4
// Recebe: Endereço inicial de uma tabela de inteiros, tamanho da tabela e endereços de 4 variáveis inteiras
// Deve colocar nas variáveis referenciadas pelos 4 ponteiros:
// número de pares, de impares, maior valor e posição do maior valor
void conta(int *t, int tam, int *np, int *ni, int *maior, int *pos){

    int i=0; *np = 0, *ni = 0, *maior = 0, *pos=0;

    for(i=0; i<tam; i++){

        if((*(t+i)%2)==0){

            (*np)++;

        }else{

            (*ni)++;

        }
    }

    for(i=0;i<tam;i++){

        if(*(t+i) > *maior){

            *maior = *(t+i);
            *pos = i;

        }
    }
}


// Exercicio 5
// Recebe: Endereço inicial e tamnaho de uma tabela de inteiros e endereços de 2 variáveis inteiras
// Deve colocar nas variáveis referenciadas pelos 2 ponteiros o maior e segundo maior elementos existentes na tabela
void procuraDupla(int *tab, int tam, int *prim, int *seg){

    int i = 0;
    *prim = *tab, *seg = *(tab+1);

    for(i=1; i < tam; i++){

     if(*(tab+i) > *prim){

         *seg = *prim;
         *prim = *(tab+i);

        }else if(*(tab+i) > *seg){

         *seg = *(tab+i);

     }
    }
}


// Deve testar o código das funções com as 3 tabelas exemplificadas na função main()

int main(){
    float x=1.2, y=4.9, z=-2.3;

    int tab0[10] = {1,3,7,5,2,10,9,7,7,1};

    int tab1[10] = {12, 7, 9, 4, 1, 4, 41, 7, 21, 14};
    int tab2[5] = {-2, -7, -8, -9, -1};
    int tab3[8] = {12, 10, 11, 5, 8, 3, -4, -1};

    int pares=0, impares=0, maior=0, posMaior=0;
    int prim=0, seg=0;

    printf("Antes: X=%.1f\tY=%.1f\tZ=%.1f\n", x, y, z);

    rotacao(&x,&y,&z);

    printf("Depois: X=%.1f\tY=%.1f\tZ=%.1f\n", x, y, z);

    //verifica_par_impar(tab0, 10);
    conta(tab0, 10, &pares, &impares, &maior, &posMaior);

    printf("Pares: %d\tImpares: %d\t, Maior: %d\t, Posicao: %d\n", pares, impares, maior, posMaior);

    procuraDupla(tab3, 8, &prim, &seg);

    printf("Maior: %d\t, Segundo Maior: %d\n", prim, seg);

    return 0;
}
