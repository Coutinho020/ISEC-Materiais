
#include "funcao.h"
#include <string.h>
#include <stdio.h>

// Nome: Diogo Coutinho Amor Antunes
// Número: 2018016615

// Deve cumprir todas as regras de submissão (ver enunciado), caso contrário o trabalho poderá não ser avaliado

void mostraTab(projeto a[], int tam){
    int i;

    for(i=0; i<tam; i++){
        printf("Projeto %d:\n", i);
        printf("Inicio: %2.2d:%2.2d:%4d\tFinal: %2.2d:%2.2d:%4d\tDuracao: %d\n",
               a[i].inicio.dia, a[i].inicio.mes, a[i].inicio.ano,a[i].final.dia, a[i].final.mes, a[i].final.ano, a[i].duracao);
        printf("Palavras chave: {%s, %s, %s, %s}\n", a[i].palavras[0], a[i].palavras[1], a[i].palavras[2], a[i].palavras[3]);
        printf("Orcamento: %d\n\n", a[i].valor);
    }
}

// Escreva o codigo da função:
// void desafio2(projeto a[], int tam);

// Recebe:
// Tabela de estruturas do tipo projeto (a)
// Dimensão da tabela (tam)

// As estruturas armazenadas na tabela têm os campos inicio, final e pal completamente preenchidos.
// Para cada uma destas estruturas, a função deve preencher os campos duracao e valor:
// 1.Colocar no campo duracao o número de dias que decorreram entre o início e o final do projeto
// 2. Colocar no campo valor o orçamento total do projeto.

int calcular_duracao(data inicio, data final){

    int dias_mes[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dias = 0;

    if(inicio.mes == final.mes){
        dias = final.dia - inicio.dia;
    }else{
        dias += dias_mes[inicio.mes - 1] - inicio.dia;
        for(int i = inicio.mes + 1; i < final.mes; i++){
            dias += dias_mes[i];
        }
        dias += final.dia;
    }
    return dias;
}

int calcular_orcamento(char palavra[]){

    int vogais = 0, tamanho = strlen(palavra);
    char v[] = "aeiou";

    char primeiro = palavra[0], ultimo = palavra[tamanho - 1];

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < 5; j++){
            if(palavra[i] == v[j]){
                vogais++;
            }
        }
    }

    int prim_vogal = 0, ult_vogal = 0;
    for(int j = 0; j < 5; j++){
        if(primeiro == v[j]){
            prim_vogal = 1;
        }
        if(ultimo == v[j]){
            ult_vogal = 1;
        }
    }

    if(vogais == 2 && prim_vogal == 1 && ult_vogal == 1){
        return 10;
    }else if(vogais == 1){
        return 5;
    }else if(vogais > 3){
        return 1;
    }
    return 0;
}

void desafio2(projeto a[], int tam){

    for(int i = 0; i < tam; i++){

        a[i].duracao = calcular_duracao(a[i].inicio, a[i].final);

        for(int j = 0; j < 4; j++){
            a[i].valor += calcular_orcamento(a[i].palavras[j]);

        }
    }
}
