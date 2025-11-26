#include <stdio.h>
#include <ctype.h>
int main() {
    FILE *f;
    char a, b, c, d, s[15];
    int i, x;
    f = fopen("main.c", "r");
    if(f == NULL) {
        printf("Erro no acesso ao ficheiro"); return 0;
    }
    a = fgetc(f);
    b = fgetc(f);
    for(i=0; i<=6; i++)
        fgetc(f);
    fgets(s, 10, f);
    fscanf(f, " %c", &c);
    do{
        d = fgetc(f);
    }while(!isdigit(d));
    ungetc(d, f);
    fscanf(f, "%d", &x);
    printf("%c %c %c %s %d\n", a, b, c, s, x);
    fclose(f);
    return 0;
}
