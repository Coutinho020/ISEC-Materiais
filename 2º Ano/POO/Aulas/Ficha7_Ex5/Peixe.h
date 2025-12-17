#ifndef FICHA7_EX5_PEIXE_H
#define FICHA7_EX5_PEIXE_H
#include <string>

class Aquario;

class Peixe {
public:
    Peixe(std::string especie, std::string cor, double peso);
    Peixe(const Peixe &p);

    std::string getEspecie() const {return especie;}
    std::string getCor() const {return cor;}
    double getPeso() const {return peso;}
    int getId() const {return id;}

    bool estaVivo() const {return vivo;}
    void matar() {vivo = false;}
    std::string getDescricao() const;
    virtual  void alimentar(double qtGramas, Aquario *aquario) = 0;
    [[nodiscard]] virtual Peixe *duplicado() const = 0;
    virtual ~Peixe() = default;

protected:
    void setPeso(double peso);

private:
    std::string especie;
    std::string cor;
    double peso;
    int id;
    bool vivo;

    static int contadorId;
};


#endif //FICHA7_EX5_PEIXE_H
