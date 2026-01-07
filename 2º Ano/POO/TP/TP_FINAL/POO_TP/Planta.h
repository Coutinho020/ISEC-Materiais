#ifndef POO_TP_PLANTA_H
#define POO_TP_PLANTA_H
#include <string>
#include "Celula.h"

class Planta {
private:

    bool viva;
    int agua;
    int nutrientes;
    bool prontaParaMultiplicar;

protected:
    void setNutrientes(int valor);
    void setAgua(int valor);
    void matar() {viva = false;}

public:

    Planta(int agua, int nutrientes);
    virtual ~Planta() = default;

    int getAgua() const { return agua; }
    int getNutrientes() const { return nutrientes; }
    void addAgua(int valor);
    void addNutrientes(int valor);

    bool estaViva() const {return viva; }
    bool querMultiplicar() const {return prontaParaMultiplicar;}
    void marcarMultiplicacao() { prontaParaMultiplicar = true; }
    void resetMultiplicacao() { prontaParaMultiplicar = false; }

    [[nodiscard]] virtual Planta* clone() const = 0;
    [[nodiscard]] virtual Planta *multiplicar() = 0;
    virtual void processaInstante(Celula& c) = 0;

    virtual char getSimbolo() const = 0;
    virtual std::string getNome() const = 0;
    virtual std::string getBeleza() const = 0;

    virtual std::string descricao() const;
};


#endif //POO_TP_PLANTA_H
