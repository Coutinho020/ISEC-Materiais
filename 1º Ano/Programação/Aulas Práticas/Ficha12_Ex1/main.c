#include <stdio.h>
#include <stdlib.h>

#define TAM 100  // versao para ficheiros com linhas com menos de 100 caracteres

// OU Exercicio 1 =>  mostrar ficheiro linha a linha com fgets()
//versao para ficheiros com linhas com menos de 100 caracteres
void mostraFicheiro_ll(char *nome_f) {
    char linha[TAM+1];
    int n = 1;
    FILE *f=fopen(nome_f,"rt");
    if (f==NULL) {
        fprintf(stderr,"Erro a abrir o ficheiro: %s\n",nome_f);
        // OU  printf("Erro a abrir o ficheiro %s\n",nome_f);
        return;
    }

    while (fgets(linha,TAM,f)){  // l� at� TAM-1 caracteres
        printf("%d: %s", n, linha);
        n++;

        // OU  puts(linha);  // coloca '\n' no final!
        // OU  printf("%s\n",linha);
    }
    fclose(f);
}

// OU Exercicio 1 => mostrar ficheiro caracter a caracter com fgetc()
void mostraFicheiro_cc(char *nome_f) {
    char c;   // OU int c;
    int n=1, novalinha=1;
    FILE *f=fopen(nome_f,"rt");
    if (f==NULL) {
        fprintf(stderr,"Erro a abrir o ficheiro: %s\n",nome_f);
        return;
    }

    while ((c=fgetc(f)) != EOF){
        if(novalinha) {
            fprintf(stdout, "%d:", n); // OU printf("%d", n);
            n++;
        }
        putchar(c);
        novalinha = (c == '\n');
        // OU      fputc(c, stdout);
        // OU      fprintf(stdout, "%c", c);
    }
    fprintf(stdout, "\n");
    fclose(f);
}

// OU Exercicio 1 => mostrar ficheiro caracter a caracter com com fscanf()
//versao para ficheiros com linhas com menos de 100 caracteres
void mostraFicheiro_ccs(char *nome_f){
    char c;
    int n = 1;
    FILE *f= fopen(nome_f,"rt");
    if(f == NULL) {
        fprintf(stderr,"\n Erro a abrir o ficheiro: %s\n", nome_f);
        return;
    }

    while (!feof(f)){
        fscanf(f,"%c", &c);
        fprintf(stdout,"%c", c);
    }
    fclose(f);
}

// CUIDADO => Exercicio 1 =>  mostrar ficheiro linha a linha com fscanf()
// Verifiquem que com a formata��o "%s" a fun��o fscanf
// ==> N�O funciona como esperado
//versao para ficheiros com linhas com menos de 100 caracteres
void mostraFicheiro_lls(char *nome_f) {
    char linha[TAM+1];
    FILE *f=fopen(nome_f,"rt");
    if (f==NULL) {
        fprintf(stderr,"Erro a abrir o ficheiro: %s\n",nome_f);
        // OU  printf("Erro a abrir o ficheiro %s\n",nome_f_f);
        return;
    }

    while (!feof(f)){
        fscanf(f, " %[^\n]", linha);
        //fputs(linha, stdout);
        puts(linha);  // coloca '\n' no final!
        // OU  printf("%s\n",linha);
    }
    fclose(f);
}

void mostraLinha(char *nome_f, int num_linha) {
    char linha[TAM + 1];
    int n = 1;

    FILE *f = fopen(nome_f, "rt");
    if (f == NULL) {
        fprintf(stderr, "Erro a abrir o ficheiro: %s\n", nome_f);
        return;
    }

    while (fgets(linha, TAM, f)) {
        if (n == num_linha) {
            printf("Linha %d: %s", num_linha, linha);
            fclose(f);
            return;
        }
        n++;
    }

    // Se chegou ao fim e não encontrou a linha
    printf("O ficheiro tem menos de %d linhas.\n", num_linha);
    fclose(f);
}

// main para demosntrar/experimentar quest�o 1
int main() {
    char nome[80];
    int linha;
    printf("Diga o nome do ficheiro: ");
    gets(nome);

    puts("\n-- Versao so com fgetc() ----------------------------"); // puts coloca '\n'
    puts("---------Caracter a Caracter---------------------------");
    mostraFicheiro_cc(nome);  // OU mostraFicheiro_cc(�original.txt�);
    puts("\n-- Versao so com fgets() ----------------------------");
    puts("---------Linha a Linha---------------------------------");
    mostraFicheiro_ll(nome);  // OU mostraFicheiro_ll(�original.txt�);
    puts("\n-- Versao so com fscanf() ---------------------------");
    puts("---------Caracter a Caracter---------------------------");
    mostraFicheiro_ccs(nome);  // OU mostraFicheiro_cc(�original.txt�);
    puts("\n-- Versao so com fscanf() ---------------------------");
    puts("---------Linha a Linha---------------------------------");
    mostraFicheiro_lls(nome);


    puts("\n---------Mostra apenas uma linha---------------------------------");
    mostraLinha(nome, 8);

    return 0;
}
