#ifndef POO_TP_INVENTARIO_H
#define POO_TP_INVENTARIO_H
#include "Ferramenta.h"
#include <vector>

class Inventario {
private:
    std::vector<Ferramenta *> ferramentas;
    Ferramenta *naMao;
    std::vector<Ferramenta *>::iterator procurar(int nrSerie);

    void libertar();
    void copia(const Inventario&);
public:
    Inventario();
    ~Inventario();

    Inventario(const Inventario& outro);
    Inventario& operator=(const Inventario& outro);

    bool adicionar(Ferramenta* f);
    Ferramenta* pegar(int nrSerie);
    bool largar();

    Ferramenta* getNaMao() const { return naMao; }

    std::string descricao() const;

    void resetUsoFerramentas();
    void eliminarFerramentaNaMao();
};


#endif //POO_TP_INVENTARIO_H
