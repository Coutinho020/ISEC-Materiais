#include <stdio.h>
#define n 10

int encontra_maior(int tab[], int dim){

    int i, maior = 0;

    for(int i = 0; i < dim; i++){

        if(tab[i] > maior){

         maior = tab[i];

        }
    }

    return maior;

}

int main() {

   int m, t[n] = {3,13,23,10,36,9, 39, 23, 11, 27 };

   m = encontra_maior(t, n);

   printf("Maior elemento: %d", m);

    return 0;
}
