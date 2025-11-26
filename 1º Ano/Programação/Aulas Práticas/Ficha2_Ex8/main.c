#include <stdio.h>
#include <string.h>
#define TAM 100

void Verifica_Frases(char string1[], char string2[], char string3[]){

    int tam1 = strlen(string1), tam2 = strlen(string2);

    if(strcmp(string1, string2) == 0){

        printf("\nStrings Iguais!!!\n");

    }else if(tam1 == tam2){

        printf("\nStrings com tamanhos iguais!!!!\n");

    }else if(tam1 < tam2){

        strcpy(string3, string1);
        strcat(string3, string2);
        printf("\n%s", string3);

    }else{

        strcpy(string3, string2);
        strcat(string3, string1);
        printf("\n%s", string3);

    }
}

int main() {

    char string1[TAM], string2[TAM], string3[TAM];

    printf("String1: ");
    gets(string1);

    printf("String2: ");
    gets(string2);

    Verifica_Frases(string1, string2, string3);
}