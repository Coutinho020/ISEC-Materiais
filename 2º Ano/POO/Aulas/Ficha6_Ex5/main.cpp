#include <iostream>
#include "Tabela.h"

using namespace std;

int main() {
    Tabela a{10, 15, 20, 25, 30, 25, 0, 0, 0, 0};
    cout << "elemento nas posicoes 2 e 3: " << a[2] << " " << a[3];
    // aparece os valores 20 e 25
    a[2] = 5;
    cout << "\na posicao 2 tem agora: " << a[2]; // aparece 5
    cout << "\nNum. De elementos com valor 25 = " << a(25) << endl;
    // aparece 2
    try {
        a[500] = 33;
        cout << "esta mensagem nao aparece";
    }
    catch (std::out_of_range e) {
        cout << "Erro: " << e.what() << "\n"; // isto aparece
    }
    return 0;
}

