#include <iostream>
#include <string>
#include <sstream>
#include <limits> // para usar numeric_limits

using namespace std;

const string str[10] = {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove", "dez"};

int traduz(string palavra) {
    for (int i = 0; i < 10; i++) {
        if (palavra == str[i]) {
            return i + 1;
        }
    }
    return 0;
}

int main() {
    string s;
    int n;

    while (true) {
        cout << "Digite um numero [1-10] ou por extenso ('fim' para sair): ";


        if (cin >> n) { // se conseguiu ler número
            if (n >= 1 && n <= 10) {
                cout << "Numero: " << n << " -> " << str[n - 1] << endl;
            } else {
                cout << "Fora do intervalo [1-10]" << endl;
            }
        } else { // se falhou ao ler número → ler palavra
            cin.clear(); // limpa o erro
            cin >> s;    // lê como string

            if (s == "fim") {
                break;
            }

            int valor = traduz(s);
            if (valor > 0) {
                cout << "Numero: " << s << " -> " << valor << endl;
            } else {
                cout << "Palavra invalida!" << endl;
            }
        }
        // limpa qualquer lixo que tenha sobrado no buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPressione ENTER para continuar...";
        cin.get(); // aguarda o Enter
        cout << endl;
    }

    return 0;
}
