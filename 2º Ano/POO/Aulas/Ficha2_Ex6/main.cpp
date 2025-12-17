#include <iostream>

using namespace std;

const int linhas = 3;
const int colunas = 4;

typedef struct Tabela{
    int matriz[linhas][colunas];
};

void PreencheMatriz(Tabela &t, int n){

    int i, j;

    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){

            t.matriz[i][j] = n;
        }
    }
}

void ImprimeMatriz(Tabela &t){

    int i, j;

    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            cout << "[" << t.matriz[i][j] << "]";
        }
        cout << endl;
    }
    cout << endl;
}

int & MudaValor(Tabela &t, int indx){

    if(indx < 0 || indx >= linhas * colunas){
        throw "Indice fora dos limites";
    }

    int lin = indx / colunas; //converte índice linear em linha
    int col = indx % colunas; // converte índice linear em coluna

    return t.matriz[lin][col];
}

int main() {

    Tabela Tab;

    PreencheMatriz(Tab, 5);
    ImprimeMatriz(Tab);

    try {
        cout << "Elemento 10 = " << MudaValor(Tab, 10) << endl; // mostra o valor atual
        MudaValor(Tab, 10) = 15; // altera o valor na posição 10
        ImprimeMatriz(Tab);
        MudaValor(Tab, 22) = 100; //devia gerar uma exceção
    }
    catch(const char * msg){
        cerr << "Erro: " << msg << endl;
    }

    return 0;
}
