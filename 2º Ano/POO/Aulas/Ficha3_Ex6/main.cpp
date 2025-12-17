#include <iostream>
#include "MSG.h"

using namespace std;

int main() {

    MSG a('a');
    MSG b{};
    MSG &c = b;
    MSG d = b;

    cout << "\nPressione ENTER para continuar: " << endl;
    cin.get();

    return 0;
}
