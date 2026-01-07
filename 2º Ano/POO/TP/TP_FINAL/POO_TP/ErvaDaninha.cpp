#include "ErvaDaninha.h"


ErvaDaninha::ErvaDaninha() : Planta(Settings::ErvaDaninha::inicial_agua, Settings::ErvaDaninha::inicial_nutrientes),
instantesDeVida(0), instantesDesdeUltimaMultiplicacao(0), jaMultiplicouAntes(false) {}



void ErvaDaninha::processaInstante(Celula &c) {

    if(!estaViva())
        return;

    instantesDeVida++;

    int aguaSolo = c.getAguaSolo();
    int aguaAbs;

    if(aguaSolo >= Settings::ErvaDaninha::absorcao_agua){
        aguaAbs = Settings::ErvaDaninha::absorcao_agua;
    }else{
        aguaAbs = aguaSolo;
    }

    c.adicionarAguaSolo(-aguaAbs);
    addAgua(aguaAbs);

    int nutSolo = c.getNutrientesSolo();
    int nutAbs;

    if(nutSolo >= Settings::ErvaDaninha::absorcao_nutrientes){
        nutAbs = Settings::ErvaDaninha::absorcao_nutrientes;
    }else{
        nutAbs = nutSolo;
    }

    c.adicionarNutrientesSolo(-nutAbs);
    addNutrientes(nutAbs);

    if(instantesDeVida >= Settings::ErvaDaninha::morre_instantes){
        matar();
        return;
    }

    if (!jaMultiplicouAntes) {
        if (getNutrientes() > Settings::ErvaDaninha::multiplica_nutrientes_maior) {
            jaMultiplicouAntes = true;
            instantesDesdeUltimaMultiplicacao = 0;
            marcarMultiplicacao();
        }
    } else {
        instantesDesdeUltimaMultiplicacao++;

        if (getNutrientes() > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
            instantesDesdeUltimaMultiplicacao >= Settings::ErvaDaninha::multiplica_instantes) {

            instantesDesdeUltimaMultiplicacao = 0;
            marcarMultiplicacao();
        }
    }
}

Planta *ErvaDaninha::multiplicar() {
    return new ErvaDaninha();
}



