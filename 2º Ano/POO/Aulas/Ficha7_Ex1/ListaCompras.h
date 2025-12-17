#ifndef FICHA7_EX1_LISTACOMPRAS_H
#define FICHA7_EX1_LISTACOMPRAS_H
#include "Coisa.h"
#include <array>
#include <string>

class ListaCompras {
public:
    bool adiciona(std::string nome, int qty); // o retorno é o sucesso da operação
    bool removeQty(std::string nome, int qty);
    bool elimina(std::string nome);
    int eliminaTodosMenoresQue(int qty); // o retorno é o número de coisas apagadas
    std::string obtemDescricao() const;
    Coisa obtemAt(int posição); // poderá não ser possível fazer esta
private:
    static const int MAX_COISAS = 20;
    std::array<Coisa, MAX_COISAS> itens;

    int procuraCoisas(const std::string &nome) const;
};


#endif //FICHA7_EX1_LISTACOMPRAS_H
