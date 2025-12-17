#include "Cao.h"
#include <sstream>
#include <cstdlib>

using namespace std;

Cao::Cao(const std::string &nome, double peso, const std::string &DataNascimento) :
        Animal("cao", nome, peso, DataNascimento) {

}

std::string Cao::exercitar() {
    ostringstream oss;
    int km = 1 + rand() % 5;

    oss << "corri " << km << " Kilometros\n";

    return oss.str();
}

std::string Cao::alimentar() {
    setPeso(0.05, 0.1, 20);

    return "biscoitos bons, obrigado\n";
}

