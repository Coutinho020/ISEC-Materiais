#ifndef FICHA7_EX1_LISTACOMPRASVECTOR_H
#define FICHA7_EX1_LISTACOMPRASVECTOR_H
#include "Coisa.h"
#include <vector>
#include <string>

class ListaComprasVector {
public:
    bool adiciona(std::string nome, int qty); // o retorno é o sucesso da operação
    bool removeQty(std::string nome, int qty);
    bool elimina(std::string nome);
    int eliminaTodosMenoresQue(int qty); // o retorno é o número de coisas apagadas
    std::string obtemDescricao() const;
    Coisa obtemAt(int posição); // poderá não ser possível fazer esta
private:
    std::vector<Coisa> itens;

    //vector<Coisa>::iterator procurarCoisa(const std::string &nome);
    auto procurarCoisa(const std::string &nome);
};

#endif //FICHA7_EX1_LISTACOMPRASVECTOR_H
