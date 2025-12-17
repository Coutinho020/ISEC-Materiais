#ifndef FICHA7_EX5_CARPA_H
#define FICHA7_EX5_CARPA_H
#include "Peixe.h"
#include <string>

class Carpa : public Peixe{
public:
    Carpa(std::string cor);

    void alimentar(double qtGramas, Aquario *aquario) override;
    [[nodiscard]] Peixe *duplicado() const override;
private:
};


#endif //FICHA7_EX5_CARPA_H
