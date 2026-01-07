#ifndef POO_TP_FERRAMENTA_H
#define POO_TP_FERRAMENTA_H
#include <string>

class Celula;

class Ferramenta {

private:
    static int contadorSerie;
    int nrSerie;
    int recursos;
    bool usadaNesteInstante;
protected:
    static const int USOS_ILIMITADOS = -1;
    void gastaDose(int v);

public:
    Ferramenta(int recursos);
    virtual ~Ferramenta() = default;

    int getNrSerie() const { return nrSerie; }
    int getRecursosRestantes() const { return recursos; }
    bool esgotou() const;

    [[nodiscard]] virtual Ferramenta* clone() const = 0;

    void marcarUsada() { usadaNesteInstante = true; }
    void resetUso()    { usadaNesteInstante = false; }
    bool jaFoiUsada() const { return usadaNesteInstante; }

    virtual bool usa(Celula &c) = 0;
    virtual char getSimbolo() const = 0;

    virtual std::string getNome() const = 0;

    virtual std::string descricao() const;
};


#endif //POO_TP_FERRAMENTA_H
