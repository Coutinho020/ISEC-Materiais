#include <stdio.h>
#include <string.h>

void InverteFrase(char fr[]) {

    printf("\nFrase a Inverter: ");
    puts(fr);
    printf("\n");

    printf("Frase invertida: ");

    int i, tam = strlen(fr);

    for (i = tam; i >= 0; i--) {

        printf("%c", fr[i]);

    }

    printf("\n");

}

int main(){

    char frase[100] = "Hoje e Domingo!";

    InverteFrase(frase);

    return 0;
}
