#include <stdio.h>
#define n 10

int cont_maior(int tab[], int dim){

    int i, maior = 0, cont_m =  1;

    for(i = 0; i < dim; i++){

        if(tab[i] > maior){

            maior = tab[i];
            cont_m = 1;

        }else if(tab[i] == maior){

            cont_m++;

        }
    }

    printf("Maior elemento: %d\n", maior);
    return cont_m;

}

int main() {

    int cont, t[n] = {3, 9 , 9, 5, 4, 9, 3, 9, 7, 8};

    cont = cont_maior(t, n);

    printf("O maior elemento aparece %d vezes!!!\n", cont);

    return 0;
}
