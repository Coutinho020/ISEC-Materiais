#ifndef P2425_DESAFIO2_FUNCAO_H
#define P2425_DESAFIO2_FUNCAO_H

typedef struct{
    int dia, mes, ano;
} data;

typedef struct dados projeto;

struct dados{
    data inicio, final;     // Datas de inicio e de final do projeto
    int duracao;            // Duracao do projeto em dias
    char palavras[4][20];   // 4 palavras-chave associadas ao projeto
    int valor;              // Orcamento total do projeto
};

void mostraTab(projeto a[], int tam);

void desafio2(projeto a[], int tam);

#endif //P2425_DESAFIO2_FUNCAO_H
