#include "MSG.h"
#include <iostream>
#include <string>

using namespace std;

int MSG::contador = 0;

MSG::MSG(char l) : letra(l), numero(contador++){
    cout << "Criado: " << getDados() << endl;
}

string MSG::getDados() const {

    ostringstream oss;
    oss << letra << "(" << numero << ")";

    return oss.str();
}

MSG::~MSG() {
    cout << "Terminado: " << getDados() << endl;
}
