#include "Cacto.h"

Cacto::Cacto() : Planta(0, 0), instantesAguaExcessiva(0), instantesNutrientesZero(0) {}

void Cacto::processaInstante(Celula &c) {

    if(!estaViva())
        return;

    int aguaSolo = c.getAguaSolo();
    int aguaAbs = (aguaSolo * Settings::Cacto::absorcao_agua_percentagem) / 100;
    c.adicionarAguaSolo(-aguaAbs);
    addAgua(aguaAbs);

    int nutSolo = c.getNutrientesSolo();
    int nutAbs;

    if(nutSolo >= Settings::Cacto::absorcao_nutrientes){
        nutAbs = Settings::Cacto::absorcao_nutrientes;
    }else{
        nutAbs = nutSolo;
    }

    c.adicionarNutrientesSolo(-nutAbs);
    addNutrientes(nutAbs);

    if(c.getAguaSolo() > Settings::Cacto::morre_agua_solo_maior){
        instantesAguaExcessiva++;
    }else{
        instantesAguaExcessiva = 0;
    }

    if(c.getNutrientesSolo() < Settings::Cacto::morre_nutrientes_solo_menor){
        instantesNutrientesZero++;
    }else{
        instantesNutrientesZero = 0;
    }

    if(instantesAguaExcessiva >= Settings::Cacto::morre_agua_solo_instantes || instantesNutrientesZero >= Settings::Cacto::morre_nutrientes_solo_instantes){
        c.adicionarNutrientesSolo(getNutrientes());
        matar();
        return;
    }

    if(getNutrientes() > Settings::Cacto::multiplica_nutrientes_maior && getAgua() > Settings::Cacto::multiplica_agua_maior){
        marcarMultiplicacao();
    }
}

Planta *Cacto::multiplicar() {
    int metadeAgua = getAgua() / 2;
    int metadeNutrientes = getNutrientes() / 2;
    addAgua(-metadeAgua);
    addNutrientes(-metadeNutrientes);

    Cacto *novo = new Cacto();
    novo->addAgua(metadeAgua);
    novo->addNutrientes(metadeNutrientes);

    return novo;
}
