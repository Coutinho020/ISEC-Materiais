#include <iostream>
#include <string>
#include "DataStore.h"
#include "UserInterface.h"

using namespace std;

int main() {

    using namespace DataStore;
    //namespace UserInterface::dadosSaoValidos;

    string nome1 = "Diogo";
    string nome2 = "antonio";
    string nome3 = "Paralelipipedo";

    cout << "\nDataStore -> a string e valida se tiver entre 5 e 10 caracteres" << endl;
    cout << "UserInterface -> a string e valida se comecar por uma maiuscula" << endl;

    cout << "\nDataStore (Diogo): " << dadosSaoValidos(nome1) << endl;
    cout << "UserInterface (Diogo): " << UserInterface::dadosSaoValidos(nome1) << endl;

    cout << "DataStore (antonio): " << dadosSaoValidos(nome2) << endl;
    cout << "UserInterface (antonio): " << UserInterface::dadosSaoValidos(nome2) << endl;

    cout << "DataStore (Paralelipipedo): " << dadosSaoValidos(nome3) << endl;
    cout << "UserInterface (Paralelipipedo): " << UserInterface::dadosSaoValidos(nome3) << endl;

    return 0;
}
