#ifndef FICHA4_EX2_ANIMAL_H
#define FICHA4_EX2_ANIMAL_H
#include <string>

class Animal {

public:
    Animal(const std::string &tipo, const std::string &nome, double peso, const std::string &dataNascimento);

    const std::string &getNome() const noexcept {return nome;}
    const std::string &getdataNascimeto() const noexcept {return dataNascimento;}
    double getPeso() const noexcept {return peso;}

    const std::string &getcodigo() const noexcept {return codigo;}
    std::string getEspecie() const;

    virtual std::string getDescricao() const;

    virtual std::string alimentar() = 0;
    virtual std::string exercitar() = 0;

    virtual ~Animal() = default;

protected:
    void setPeso (double percentagem, double minPeso, double maxPeso);

private:
    std::string nome;
    double peso;
    std::string dataNascimento;
    std::string codigo;
    static int contador;

    static std::string getNovoCodigo(const std::string &tipo);
};

#endif //FICHA4_EX2_ANIMAL_H
