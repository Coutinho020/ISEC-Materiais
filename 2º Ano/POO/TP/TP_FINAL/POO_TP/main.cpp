#include <cstdlib>
#include <ctime>
#include "Simulador.h"

using namespace std;

int main() {

    srand((unsigned)std::time(nullptr));

    Simulador simulador;
    simulador.lerComandos();

    return 0;
}
