#include <stdio.h>
#define n 10

int cont_mais(int tab[], int dim){

    int i, j, maior = 0, mais_comum = 0, cont = 1;

    for(i = 0; i < dim; i++){
        for(j = i + 1; j < dim; j++){

            if(tab[j] == tab[i]){

                cont++;

            }
        }

        if(cont == mais_comum && tab[i] > maior){

            maior = tab[i];

        }else if(cont > mais_comum){

            mais_comum = cont;
            maior = tab[i];

        }

        cont = 1;

    }

    printf("Elemento que aparece mais vezes: %d\n", maior);
    return mais_comum;

}

int main() {

    int mais_m, tab[n] = {3, 9 ,5, 9, 9, 4, 8, 5, 5, 5 };

    mais_m = cont_mais(tab, n);

    printf("Aparece %d vezes!!!\n", mais_m);
    return 0;
}
