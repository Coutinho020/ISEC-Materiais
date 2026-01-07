#ifndef POO_TP_PLANTAEXOTICA_H
#define POO_TP_PLANTAEXOTICA_H
#include "Planta.h"
#include "Celula.h"

class PlantaExotica : public Planta {
private:
    int instantesBaixaAgua;
    int getAltura() const;
public:

    PlantaExotica();

    char getSimbolo() const override {return 'x';}
    std::string getNome() const override {return "PlantaExotica";}
    std::string getBeleza() const override {return "neutra";}

    Planta* clone() const override { return new PlantaExotica(*this); }

    [[nodiscard]] Planta *multiplicar() override;
    void processaInstante(Celula &c) override;

    static const int inicial_agua = 40;
    static const int inicial_nutrientes = 40;
    static const int agua_absorvida_solo = 5;
    static const int nutrientes_absorvida_solo = 5;
    static const int perda_agua_instante = 3;
    static const int agua_perda_percentagem_multiplicacao = 40;
    static const int nutrientes_perda_percentagem_multiplicacao = 40;
    static const int morre_agua_menor = 10;
    static const int morre_instantes = 5;
    static const int multiplica_altura_maior = 120;
};


#endif //POO_TP_PLANTAEXOTICA_H
