#ifndef FICHA7_EX5_TUBARAO_H
#define FICHA7_EX5_TUBARAO_H
#include "Peixe.h"
#include <string>

class Tubarao : public Peixe{

    Tubarao(std::string cor);

    void alimentar(double qtGramas, Aquario *aquario) override;
    [[nodiscard]] Peixe *duplicado() const override;
};


#endif //FICHA7_EX5_TUBARAO_H
