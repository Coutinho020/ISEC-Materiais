#include <stdio.h>

typedef struct{
    char nome[100];
    int id;
}pessoa;

void f(){
    FILE *f;
    pessoa a;
    int x;
    f = fopen("dados.bin", "rb");
    if(f == NULL) return;
    fread(&a, sizeof(pessoa), 1, f);
    printf("%s\t(%d)\n", a.nome, a.id);

    fread(&a, sizeof(pessoa), 1, f);
    printf("%s\t(%d)\n", a.nome, a.id);

    fseek(f, 3 * sizeof(pessoa), SEEK_SET);
    x = ftell(f);
    fread(&a, sizeof(pessoa), 1, f);
    printf("%s\t(%d)\n", a.nome, a.id);

    fseek(f, 2*sizeof(pessoa), SEEK_CUR);
    fread(&a, sizeof(pessoa), 1, f);
    printf("%s\t(%d)\n", a.nome, a.id);

    fseek(f, -x, SEEK_END);
    fread(&a, sizeof(pessoa), 1, f);
    printf("%s\t(%d)\n", a.nome, a.id);

    fclose(f);
}

int main(){

    f();

    return 0;
}
