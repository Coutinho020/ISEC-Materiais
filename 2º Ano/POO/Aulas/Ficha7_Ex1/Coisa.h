#ifndef FICHA7_EX1_COISA_H
#define FICHA7_EX1_COISA_H
#include <string>

class Coisa {
public:
    Coisa(std::string n, int q);
    Coisa() : nome(""), qty(0){}

    std::string getNome() const;
    int getQty () const;

    void atualizaQty(int dif);
    std::string descricao() const;

    //bool operator<(const Coisa &coisa) const;
private:
    std::string nome;
    int qty;
};

#endif //FICHA7_EX1_COISA_H
