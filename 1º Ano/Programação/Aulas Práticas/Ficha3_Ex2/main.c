#include <stdio.h>

void f2(int x, int *p){
    printf("F2: Endereco/Localizacao: x=%p\tb=%p\n", &x, p);
    x++;
    (*p)++;
    printf("Valores em F2: a=%d\tb=%d\n", x, *p);
}
int main(){
    int a=1, b=2;
    printf("Valores Iniciais: a=%d\tb=%d\n", a, b);
    printf("Main: Endereco/Localizacao: a=%p\tb=%p\n", &a, &b);
    f2(a, &b);
    printf("Valores Finais: a=%d\tb=%d\n", a, b);
}
