#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Gato.h"
#include "Cao.h"
#include "Clinica.h"

using namespace std;

int main() {
    /*
    //srand(123);
    srand(time(nullptr));

    for(int i = 0; i < 10; i++)
        cout << rand() % 100 << endl;

    cout << "-------------------------------" << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100);
    for(int i = 0; i < 10; i++)
        cout << dist(gen) << endl;
*/

    Gato g("Tobias", 8.54, "19/07/2015");
    Cao c("Orelhas", 15.7, "24/03/2020");

    Clinica clinica;

    clinica.AddAnimal(g);
    clinica.AddAnimal(c);

    cout <<  clinica.getListaAnimais();

    cout << clinica.alimentarAnimais();

    cout <<  clinica.getListaAnimais();

    cout << clinica.exercitarAnimais();

    return 0;
}
