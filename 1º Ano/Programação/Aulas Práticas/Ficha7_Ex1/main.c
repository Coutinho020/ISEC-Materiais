#include <stdio.h>
#include <stdlib.h>

void preenche(int *a, int tam){
    for(int i=0; i<tam; i++)
        a[i] = 5*i;
}

void mostra_array(int *a, int tam){

    int i;

    if(tam == 0){
        printf("Tabela Vazia!!!\n");
    }else {
        for (i = 0; i < tam; i++) {
            printf("%d\t", a[i]);
        }
    }
    printf("\n");
}

int* f1(int *a, int *tam){
    int *p, i;
    p = realloc(a, sizeof(int)*(*tam + a[1]));
    if(p == NULL)
        return a;
    a = p;
    preenche(a + *tam, a[1]);
    *tam += a[1];
    return a;
}
int main(){
    int *v = NULL, total = 0;
    mostra_array(v, total);
    v = malloc(sizeof(int) * 3);
    if(v == NULL)
        return 0;
    total = 3;
    preenche(v, total);
    mostra_array(v, total);
    v = f1(v, &total);
    mostra_array(v, total);
    free(v);
    v = NULL;
    total = 0;
    mostra_array(v, total);
    return 0;
}
