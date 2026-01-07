#ifndef POO_TP_ERVADANINHA_H
#define POO_TP_ERVADANINHA_H
#include "Planta.h"
#include "Settings.h"
#include "Celula.h"

class ErvaDaninha : public Planta {
private:
    int instantesDeVida;
    int instantesDesdeUltimaMultiplicacao;
    bool jaMultiplicouAntes;

public:

    ErvaDaninha();

    char getSimbolo() const override {return 'e';}
    std::string getNome() const override {return "ErvaDaninha";}
    std::string getBeleza() const override {return "feia";}

    Planta* clone() const override { return new ErvaDaninha(*this); }

    [[nodiscard]] Planta *multiplicar() override;
    void processaInstante(Celula &c) override;
};

#endif //POO_TP_ERVADANINHA_H
