//
// Created by diogo on 09/10/2025.
//

#ifndef FICHA3_EX3_PESSOA_H
#define FICHA3_EX3_PESSOA_H
#include <string>

class Pessoa {
public:
    Pessoa(std::string nome, std::string id, int idade);
    std::string getNome() const;
    std::string getID() const;
    int getIdade() const;

    bool setNome(std::string nome);
    bool setIdade(int idade);

    std::string getAsString() const;

    ~Pessoa();

private:
    std::string nome, id;
    int idade;
};


#endif //FICHA3_EX3_PESSOA_H
