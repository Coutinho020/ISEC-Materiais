#include <stdio.h>
#define n 6

int inverte_tabela(int tab[], int dim){

    int i = 1;

    for(dim - i; i <= dim; i++){

        printf("[%d] ", tab[dim-i]);

    }

    return 0;
}

int main() {

    int t[n] = {1,2,3,4,5, 6};

    inverte_tabela(t, n);

    return 0;
}
