#ifndef POO_TP_FERRAMENTA_H
#define POO_TP_FERRAMENTA_H
#include <string>

class Celula;

class Ferramenta {

private:
    static int contadorSerie;
    int nrSerie;
    int recursos;

protected:
    static const int USOS_ILIMITADOS = -1;

public:
    Ferramenta(int recursos);
    virtual ~Ferramenta() = default;

    virtual void usa(Celula &c) = 0;
    virtual char getSimbolo() const = 0;
    virtual std::string getNome() const = 0;

    int getNrSerie() const { return nrSerie; }
    int getRecursosRestantes() const { return recursos; }

    bool gastaDose(int dose);

    virtual std::string descricao() const;
};


#endif //POO_TP_FERRAMENTA_H
