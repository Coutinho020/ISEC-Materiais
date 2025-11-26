#include <stdio.h>
#include "tabela.h"

void printV(ret a[], int total){
    int i;

    printf("Existem %d retangulos na tabela\n", total);
    for(i=0; i<total; i++) {
        printf("R. %d\n", i);
        printRet(a[i]);
    }
}

int addRet(ret a[], int *total){

    if(*total >= 10){

        printf("Tabela Completa!!!\n");
        return 0;
    }else{

        initRet(&a[*total]);
        (*total)++;
        return 1;
    }
}

void duplicaAltLarg(ret a[], int total){

    for(int i = 0; i < total; i++){

     if(areaR(a[i])%2 == 0){

         a[i].alt *= 2;
         a[i].larg *= 2;
     }
    }
}


int quadrante1(ret a[], int total){

    int total_q1 = 0;

    printf("\n");

    for(int i = 0; i < total; i++){

     if(quadrante(a[i].canto) == 1)

         total_q1++;

    }
    return total_q1++;
}

void eliminaMenor(ret a[], int *total){

    int  menor_a = areaR(a[0]), i_ma = 0;

    for(int i = 0; i < *total; i++){

        printf( "Area reatangulo %d: %d\n", i, areaR(a[i]));

    }

    for(int i = 1; i < *total; i++){

        if(areaR(a[i]) < menor_a){
            menor_a = areaR(a[i]);
            i_ma = i;
        }
    }

    for(int j = i_ma; j < *total - 1; j++){

        a[j] = a[j + 1];

    }

    (*total)--;
}

void eliminaVarios(ret a[], int *total, int lim){

    for(int i = 0; i < *total; i++){

        printf( "Area reatangulo %d: %d\n", i, areaR(a[i]));

    }

    for(int i = 0; i < *total; i++){


        if(areaR(a[i]) < lim){

            for(int j = i; j < *total - 1; j++){

                a[j] = a[j+1];

            }

            (*total)--;
            i--;

        }
    }
}
