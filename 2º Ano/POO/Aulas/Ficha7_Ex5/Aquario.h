#ifndef FICHA7_EX5_AQUARIO_H
#define FICHA7_EX5_AQUARIO_H
#include <string>
#include <vector>
#include "Peixe.h"

class Aquario {
public:
    Aquario(){}
    Aquario &operator=(const Aquario &aquario);

    void adicionarPeixe(const Peixe &p);
    void removerPeixe(int id);
    const Peixe *obterPeixe(int id) const;
    Peixe *obterPeixeExcepto(int id) const;
    void alimentarPeixes(double qtGramas);
    void listarPeixes();
    ~Aquario();
private:
    std::vector<Peixe *> peixes;
    void apagarTodosOsPeixes();
    void removerPeixesMortos();

    int procurarPeixe(int id) const;
};


#endif //FICHA7_EX5_AQUARIO_H
