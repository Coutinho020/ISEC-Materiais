#ifndef POO_TP_PLANTA_H
#define POO_TP_PLANTA_H
#include "Solo.h"
#include <string>
#include "Celula.h"

class Planta {
private:

    bool viva;
    int agua;
    int nutrientes;
    int nutrientesAbsorvidosVida;
    int aguaAbsorvidaVida;

protected:
    void setAgua(int valor) { agua = valor; }
    void setNutrientes(int valor) { nutrientes = valor; }
    void addNutrientesAbsorvidosVida(int valor) { nutrientesAbsorvidosVida += valor; }
    void addAguaAbsorvidaVida(int valor) { aguaAbsorvidaVida += valor; }

public:

    Planta(int agua, int nutrientes);

    virtual ~Planta() = default;

    virtual void processaInstante(Celula &c) = 0;

    virtual char getSimbolo() const = 0;
    virtual std::string getNome() const = 0;
    virtual std::string getBeleza() const = 0;

    bool estaViva() const {return viva; }
    void matar() {viva = false;}

    int getAguaAcumulada() const { return agua; }
    int getNutrientesAcumulados() const { return nutrientes; }

    virtual std::string descricao() const;
};


#endif //POO_TP_PLANTA_H
