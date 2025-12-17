#ifndef FICHA4_EX1_IMOBILIARIA_H
#define FICHA4_EX1_IMOBILIARIA_H
#include "Imovel.h"

class Imobiliaria {
public:
    Imobiliaria();
    int getNumImoveis() const {return nImoveis;}
    bool addImovel(Imovel *imoveis);

    std::string ListaTodos() const;
    std::string ListaAndar(int andar) const;

    const Imovel *getImovel(const std::string &codigo) const; //Ponteiro só de leitura

    std::string getDescricaoImovel(const std::string &codigo) const;

    bool RemoverImovel(const std::string &codigo);

    void aumentarPrecos();

private:
    static const unsigned int Max_Imoveis = 100;
    Imovel *imoveis[Max_Imoveis];
    int nImoveis;

    int procurarImovel(const std::string &codigo) const;
};


#endif //FICHA4_EX1_IMOBILIARIA_H
