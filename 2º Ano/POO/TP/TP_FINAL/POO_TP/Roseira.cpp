#include "Roseira.h"

Roseira::Roseira() : Planta(Settings::Roseira::inicial_agua, Settings::Roseira::inicial_nutrientes) {}

void Roseira::processaInstante(Celula &c) {

    if(!estaViva())
        return;

    addAgua(-Settings::Roseira::perda_agua);
    addNutrientes(-Settings::Roseira::perda_nutrientes);

    int aguaSolo = c.getAguaSolo();
    int aguaAbs;

    if(aguaSolo >= Settings::Roseira::absorcao_agua){
        aguaAbs = Settings::Roseira::absorcao_agua;
    }else{
        aguaAbs = aguaSolo;
    }

    c.adicionarAguaSolo(-aguaAbs);
    addAgua(aguaAbs);

    int nutSolo = c.getNutrientesSolo();
    int nutAbs;

    if(nutSolo >= Settings::Roseira::absorcao_nutrientes){
        nutAbs = Settings::Roseira::absorcao_nutrientes;
    }else{
        nutAbs = nutSolo;
    }

    c.adicionarNutrientesSolo(-nutAbs);
    addNutrientes(nutAbs);

    if(getAgua() <= Settings::Roseira::morre_agua_menor || getNutrientes() < Settings::Roseira::morre_nutrientes_menor
    || getNutrientes() > Settings::Roseira::morre_nutrientes_maior){

        c.adicionarAguaSolo(getAgua() / 2);
        c.adicionarNutrientesSolo(getNutrientes() / 2);

        matar();
        return;
    }

    if(getNutrientes() > Settings::Roseira::multiplica_nutrientes_maior){
        marcarMultiplicacao();
    }
}

Planta *Roseira::multiplicar(){
    int aguaAtual = getAgua();

    int aguaNova = (aguaAtual * Settings::Roseira::nova_agua_percentagem) / 100;

    int aguaOriginal = (aguaAtual * Settings::Roseira::original_agua_percentagem) / 100;

    int diferenca = aguaAtual - (aguaNova + aguaOriginal);
    aguaOriginal += diferenca;

    setAgua(aguaOriginal);
    setNutrientes(Settings::Roseira::original_nutrientes);

    Roseira* novo = new Roseira();
    novo->setAgua(aguaNova);
    novo->setNutrientes(Settings::Roseira::nova_nutrientes);

    return novo;
}


