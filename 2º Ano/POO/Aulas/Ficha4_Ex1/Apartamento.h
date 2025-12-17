#ifndef FICHA4_EX1_APARTAMENTO_H
#define FICHA4_EX1_APARTAMENTO_H
#include "Imovel.h"

class Apartamento : public Imovel{
public:
    Apartamento(double area, int andar, unsigned int assoalhadas);

    unsigned int getAssoalhadas() const {return assoalhadas;}

    virtual std::string getDescricao() const override;

protected:
    double getPercentagem() override;

private:
    unsigned int assoalhadas;
};


#endif
