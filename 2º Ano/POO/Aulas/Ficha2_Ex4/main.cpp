#include <iostream>

using namespace std;

void troca(int &a, int &b){

    int temp = a;
    a = b;
    b = temp;

}

/*

//Nao faz sentido, pois recebendo , pois nao se podem alterar valores de constantes

void troca(const int &a, const int &b){
    int temp = a;
}

*/

int main() {

    int a = 5, b = 10;
    troca(a, b);
    cout << "\na = " << a << "\nb = " << b;

    return 0;
}
