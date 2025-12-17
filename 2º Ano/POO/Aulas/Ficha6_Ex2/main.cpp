#include <iostream>
#include "Hora.h"

using namespace std;

int main() {

    Hora a(10,30), b(2), c;
    b += 90; // acrescenta 90 minutos (1h30) a b (se ultrapassar 23h59 “dá a volta”)
    a += b; // acrescenta b a a (mantendo sempre os valores dentro dos limites 23h59)
    cout << a << b; // mostra as horas de a e de b
    cin >> a >> b; // lê 4 inteiros e canaliza-os para as horas de a, minutos de a, e depois para b
    if (a) {
       cout << "Hora a : 0h:0 min" << endl;
   } // executa se a hora a for 0h0
   if (!a) {
       cout << "Hora a nao e 0h:0 min" << endl;
   } // executa se a hora a não for 0h0
   if (a == b) {
       cout << "Hora a = Hora b" << endl;
   } // executa se as horas a e b forem iguais
    if (a > b) {
    cout << "hora a > hora b" << endl;
} // executa se as horas a for maior (mais tarde que) a hora b
    int totalMinutos = b; // totalMinutos fica com o número total de minutos em b
    cout << totalMinutos << endl;
    c = a+b; // soma as horas a e b e coloca em c. Não alterem nem a nem b
   cout << c << endl;
    // a++; // incrementa os minutos de a (e talvez a hora, se exceder 59 min)
   // ++b; // incrementa as horas de b (não esquecer que depois de 23 passa para 0)

    return 0;
}
