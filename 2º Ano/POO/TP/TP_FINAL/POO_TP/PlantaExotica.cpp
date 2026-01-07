#include "PlantaExotica.h"

PlantaExotica::PlantaExotica() : Planta(inicial_agua, inicial_nutrientes), instantesBaixaAgua(0){}

int PlantaExotica::getAltura() const {
    return getAgua() + getNutrientes();
}

void PlantaExotica::processaInstante(Celula &c) {
    if(!estaViva())
        return;

    addAgua(-perda_agua_instante);

    int aguaSolo = c.getAguaSolo();
    int aguaAbs;

    if(aguaSolo >= agua_absorvida_solo){
        aguaAbs = agua_absorvida_solo;
    }else{
        aguaAbs = aguaSolo;
    }

    c.adicionarAguaSolo(-aguaAbs);
    addAgua(aguaAbs);

    int nutSolo = c.getNutrientesSolo();
    int nutAbs;

    if(nutSolo >= nutrientes_absorvida_solo){
        nutAbs = nutrientes_absorvida_solo;
    }else{
        nutAbs = nutSolo;
    }

    c.adicionarNutrientesSolo(-nutAbs);
    addNutrientes(nutAbs);

    if(getAgua() < morre_agua_menor){
        instantesBaixaAgua++;
    }else{
        instantesBaixaAgua = 0;
    }

    if(instantesBaixaAgua >= morre_instantes){
        c.adicionarNutrientesSolo(getNutrientes());
        matar();
        return;
    }

    if(getAltura() >= multiplica_altura_maior){
        marcarMultiplicacao();
    }
}

Planta *PlantaExotica::multiplicar() {
    int perdaAgua = (getAgua() * agua_perda_percentagem_multiplicacao) / 100;
    int perdaNutrientes = (getNutrientes() * nutrientes_perda_percentagem_multiplicacao) / 100;

    addAgua(-perdaAgua);
    addNutrientes(-perdaNutrientes);

    PlantaExotica *novo = new PlantaExotica();

    novo->addAgua(inicial_agua / 2);
    novo->addNutrientes(inicial_nutrientes / 2);

    return novo;
}
