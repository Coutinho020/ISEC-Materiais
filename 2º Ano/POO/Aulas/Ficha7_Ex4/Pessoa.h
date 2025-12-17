#ifndef FICHA7_EX4_PESSOA_H
#define FICHA7_EX4_PESSOA_H
#include <string>

class Pessoa {
public:
    Pessoa(std::string nome, int bi, int nif);

    std::string getNome() const;

    int getBI() const; // Critério de igualdade é o BI ("cartão de cidadão")
    int getNIF() const;

    void setNome(std::string nome);

    std::string descricao() const;

private:
    std::string nome;
    int bi, nif;
} ;


#endif //FICHA7_EX4_PESSOA_H
