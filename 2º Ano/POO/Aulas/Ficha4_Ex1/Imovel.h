#ifndef FICHA4_EX1_IMOVEL_H
#define FICHA4_EX1_IMOVEL_H
#include <string>

class Imovel {
public:

    std::string getCodigo() const {return codigo;}

    double getPreco() const {return preco;}
    double getArea() const {return area;}
    int getAndar() const {return andar;}

    virtual std::string getDescricao() const;
    void aumentarPreco();
    virtual ~Imovel() = default;

protected:
    virtual double getPercentagem() = 0;
    Imovel(const std::string &prefixo, double area, double preco, int andar = 0);
    //Como o construtor Imovel nao vai ser usado coloca-se como protected

private:
    double area, preco;
    int andar;
    std::string codigo;
    unsigned static int contador;

    static std::string getNovoCodigo(const std::string &prefixo);
};



#endif
