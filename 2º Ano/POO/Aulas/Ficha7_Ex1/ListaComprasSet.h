#ifndef FICHA7_EX1_LISTACOMPRASSET_H
#define FICHA7_EX1_LISTACOMPRASSET_H
#include <string>
#include <set>
#include "Coisa.h"

class ListaComprasSet {
public:
    bool adiciona(std::string nome, int qty); // o retorno é o sucesso da operação
    bool removeQty(std::string nome, int qty);
    bool elimina(std::string nome);
    int eliminaTodosMenoresQue(int qty); // o retorno é o número de coisas apagadas
    std::string obtemDescricao() const;
    //Coisa obtemAt(int posição); // poderá não ser possível fazer esta
private:
    std::set<Coisa> itens;

   //set<Coisa>::iterator procuraCoisa(const std::string &nome);
   auto procuraCoisa(const std::string &nome);
};

bool operator<(const Coisa &coisa1, const Coisa &coisa2);

#endif //FICHA7_EX1_LISTACOMPRASSET_H
