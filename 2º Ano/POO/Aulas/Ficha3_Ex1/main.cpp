#include <iostream>

using namespace std;

const int linhas = 3;
const int colunas = 4;

typedef struct Tab{
    int matriz[linhas][colunas];

void PreencheMatriz( int n){

    int i, j;

    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){

            matriz[i][j] = n;
        }
    }
}

void ImprimeMatriz(){

    int i, j;

    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            cout << "[" << matriz[i][j] << "]";
        }
        cout << endl;
    }
    cout << endl;
}

int & MudaValor(int indx){  //Nao e preciso colocar MudaValor(Tab &t, int indx), pois na chamada já se indica a.MudaValor

    if(indx < 0 || indx >= linhas * colunas){
        throw "Indice fora dos limites";
    }

    int lin = indx / colunas; //converte índice linear em linha
    int col = indx % colunas; // converte índice linear em coluna

    return matriz[lin][col];  //Aqui no return igual, não é necessario colocar t.matriz[][]
}

}Tabela;

int main() {

    Tabela a;

    a.PreencheMatriz(5);
    a.ImprimeMatriz();

    try {
        cout << "Elemento 10 = " << a.MudaValor(10) << endl << endl; // mostra o valor atual
        a.MudaValor(10) = 15; // altera o valor na posição 10
        a.ImprimeMatriz();
        a.MudaValor(22) = 100; //devia gerar uma exceção
        a.ImprimeMatriz();
    }
    catch(const char * msg){
        cerr << "\nErro: " << msg << endl;
    }

    return 0;
}
