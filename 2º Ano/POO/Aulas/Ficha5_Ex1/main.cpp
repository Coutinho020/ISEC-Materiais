#include <iostream>
#include "MyString.h"

using namespace std;

int main() {

    MyString a; // sem caracteres nenhuns (ou seja, apenas '\0', se usar esse terminador)
    MyString b("Ola"); // com “Ola”
    //MyString x = b;

    b.acrescenta("mundo"); // fica com "Olamundo"
    cout << b.obtemCString() << endl; // aparece "Olamundo"
    b.removeDeAte(2,4); // remove os caracteres índice 2 a 4, inclusive ("amu")
    // valida índices e retorna false em caso de índices inválidos
    cout << b.obtemCString() << endl; // aparece "Olndo". Dá para ver, mas não para alterar
    // nesta funcionalidade, dá jeito ter o '\0' como habitual
    b=a; // a e b ficam com informação igual
    MyString c("abc"); // Nova MyString com "abc"
    a=c; // a fica agora também com "abc"
    c.mudaCharAt(1,'x'); // c foi mudada para "axc" (retorna false se não puder)
    cout << c.obtemCString() << endl; // aparece "axc" (confirma-se que c foi mudada)
    cout << a.obtemCString() << endl; // aparece "abc" (ou seja, a não foi alterada)
    a="12345";

  return 0;
}
