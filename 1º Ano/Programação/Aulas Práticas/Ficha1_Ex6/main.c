#include <stdio.h>
#define n 6

int desloca_tab(int tab[], int dim){

    int i; tab[0] = tab[dim - 1];

    for(i = dim - 2; i >= 0; i--){

        tab[i] = tab[i -1];

    }

    for(i = 0; i >= 0; i++){

     printf("[%d] ", tab[i]);

    }

    return 0;
}

int main() {

    int t[n] = {1, 2,3, 4, 5};

    desloca_tab(t, n);

    return 0;
}
