#ifndef FICHA4_EX1_LOJA_H
#define FICHA4_EX1_LOJA_H
#include "Imovel.h"

class Loja : public Imovel{
public:
    Loja(double area);

    virtual std::string getDescricao() const override;

protected:

    double getPercentagem() override;
private:
};


#endif //FICHA4_EX1_LOJA_H
