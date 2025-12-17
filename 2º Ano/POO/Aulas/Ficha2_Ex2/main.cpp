#include <iostream>

using namespace std;

void imprime(string s){

    cout << "\nRecebe apenas uma string por argumento: " << endl;
    cout << "String: " << s << endl;
}

void imprime(string s, int n){

    cout << "\nRecebe uma string e um inteiro: " << endl;
    cout << "String: " << s << endl;
    cout << "Numero: " << n << endl;
}

void imprime(int n, string s){

    cout << "\nRecebe uma string e um inteiro, mas com ordem diferente: " << endl;
    cout << "Numero: " << n << endl;
    cout << "String: " << s << endl;

}

int main() {

    imprime("programacao orientada a objetos");
    imprime("horas por aula teorica ", 2);
    imprime(3, " horas em cada aula pratica");


    return 0;
}
