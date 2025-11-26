#include <stdio.h>

int calcularSomaEMedia(char *nomeFicheiro, int *soma, float *media) {

    FILE *ficheiro = fopen(nomeFicheiro, "rb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro");
        return -1;
    }

    int valor;
    int contador = 0;
    *soma = 0;

    while (fread(&valor, sizeof(int), 1, ficheiro) == 1) {
        *soma += valor;
        printf("Valor %d: %d\n", contador, valor);
        contador++;
    }

    fclose(ficheiro);

    if (contador == 0) {
        *media = 0.0;
        return 0;  // Nenhum valor lido
    }

    *media = (float)(*soma) / contador;
    return 0;  // Sucesso
}

int verificarOrdemCrescente(char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "rb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro");
        return 0;
    }

    int anterior, atual;

    // Verifica se há pelo menos um valor
    if (fread(&anterior, sizeof(int), 1, ficheiro) != 1) {
        fclose(ficheiro);
        return 0;  // Considera-se crescente se estiver vazio ou tiver apenas um valor
    }

    // Percorre os restantes valores
    while (fread(&atual, sizeof(int), 1, ficheiro) == 1) {
        if (atual < anterior) {
            fclose(ficheiro);
            return 0;  // Não é estritamente crescente
        }
        anterior = atual;
    }

    fclose(ficheiro);
    return 1;  // É estritamente crescente
}

int main() {
    int soma;
    float media;

    if (calcularSomaEMedia("valoresEx2.bin", &soma, &media) == 0) {
        printf("Soma: %d\n", soma);
        printf("Media: %.2f\n", media);
    }

    if (verificarOrdemCrescente("valoresEx2.bin")) {
        printf("\nO ficheiro esta em ordem estritamente crescente.\n");
    } else {
        printf("\nO ficheiro nao esta em ordem estritamente crescente.\n");
    }

    return 0;
}
