#include <iostream>
#include <initializer_list>

using namespace std;

const int linhas = 3;
const int colunas = 4;
const int TAM = 6;

class Tabela{

    int matriz[linhas][colunas];
    int conjunto[TAM];

public:
    // 1 e 2) Construtor default -> inicializa com zeros ou com valor recebido
    Tabela(int valor = 0){
        PreencheMatriz(valor);
        cout << "[Construtor] default -> " << valor << endl;
    }

    // 3) Construtor que cria uma sequência crescente (a, a+b, a+2b, ...)
    Tabela(int a, int b){
        int total = linhas * colunas;
        cout << "[Construtor] progressao -> a=" << a << " b=" << b << "\n";
        for(int i = 0; i < total; i++){
            int lin = i / colunas;
            int col = i % colunas;
            matriz[lin][col] = a + b;
            b++;
        }
    }

    // 4) Construtor initializer_list
    Tabela(initializer_list<int> lista){
        cout << "[Construtor] initializer_list " << endl;
        PreencheMatriz(0);
        int i = 0;
        int total = linhas * colunas;
        for(int elemento : lista){
            if(i >= total){
                break;
            }
            int lin = i / colunas;
            int col = i % colunas;
            matriz[lin][col] = elemento;
            i++;
        }
    }

void PreencheMatriz(int n){

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){

            matriz[i][j] = n;
        }
    }
}

// Imprime a matriz (não altera o objeto) → const
void ImprimeMatriz() const{

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            cout << "[" << matriz[i][j] << "]";
        }
        cout << endl;
    }
    cout << endl;
}

int & Elemento(int indx) {  //Nao e preciso colocar Elemento(Tab &t, int indx), pois na chamada já se indica a.MudaValor

    if (indx < 0 || indx >= linhas * colunas) {
        throw "Indice fora dos limites";
    }

    int lin = indx / colunas; //converte índice linear em linha
    int col = indx % colunas; // converte índice linear em coluna

    return matriz[lin][col];  //Aqui no return igual, não é necessario colocar t.matriz[][]
    }

    bool contem(int valor) const{
        for (int i = 0; i < linhas; i++){
            for(int j = 0; j < colunas; j++){
                if(matriz[i][j] == valor){
                    return true;
                }
            }
        }
        return false;
    }

    //1f -> Neste caso não consigo testar pois criei o construtor para tratar matrizes[i][j]
    bool eIgual(Tabela outra) const{
        //conjunto[i] comparar com outra.conjunto[j]
        //[5, 2, 3, 4, 1] não é igual [-999, 5, -999, -9999, 1]
        bool resultado=true;
        for(int elemento: conjunto) {
            int j;
            for (j=0; j < TAM; j++)
                if(elemento == outra.conjunto[j]){
                    outra.conjunto[j] = -999;
                    break;
                }
            if(j==TAM){
                resultado=false;
                break;
            }
        }
        return resultado;
    }
};

int main() {

    Tabela a;
    a.ImprimeMatriz();

    try {
        cout << "Elemento 10 = " << a.Elemento(10) << endl << endl; // mostra o valor atual
        a.Elemento(10) = 15; // altera o valor na posição 10
        a.ImprimeMatriz();
        a.Elemento(22) = 100; //devia gerar uma exceção
        a.ImprimeMatriz();
    }
    catch(const char * msg){
        cerr << "\nErro: " << msg << endl;
    }

    //1c) 4 versões de construtores
    Tabela b; //preenchida com zeros
    b.ImprimeMatriz();
    Tabela c(10); //preenchida com o valor indicado
    c.ImprimeMatriz();
    Tabela d(1, 2); //preenche com a sequência 1, (1+2)3, (1+3)4, (1+4)5, ...
    d.ImprimeMatriz();
    Tabela e({4, 5, 6}); //preenche com a lista indicada, o resto fica com 0's
    e.ImprimeMatriz();

    //1e) verificar se um número existe dentro da tabela
    if(e.contem(5)) //devia ser verdadeiro
        cout << "\nA matriz e tem o valor 7\n";
    else
        cout << "\nNao existe o valor 7 na matriz e\n";

    //1f) verificar se duas tabelas têm o mesmo conteúdo
    Tabela f;
    if(b.eIgual(f)) //devia ser verdadeiro
        cout << "\nAs tabelas b e f são iguais!\n";
    else
        cout << "\nAs tabelas b e f nao sao iguais!\n";

    return 0;
}
