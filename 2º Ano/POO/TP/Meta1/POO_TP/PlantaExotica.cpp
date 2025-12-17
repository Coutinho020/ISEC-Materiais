#include "PlantaExotica.h"

PlantaExotica::PlantaExotica() : Planta(40, 40), instantesBaixaAgua(0) {}

int PlantaExotica::getAltura() const {

    return getAguaAcumulada() + getNutrientesAcumulados();
}

void PlantaExotica::processaInstante(Celula &c) {

}