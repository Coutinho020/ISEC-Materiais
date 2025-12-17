#ifndef FICHA7_EX4_PAIS_H
#define FICHA7_EX4_PAIS_H
#include <string>
#include <vector>
#include "Pessoa.h"

class Pais {
public:
    Pais(std::string nome) : nome(nome){}
    Pais(const Pais &outro);
    Pais &operator = (const Pais &outro);
    ~Pais();

    std::string getNome() const {return nome;}
    bool adicionarPessoa(const std::string &nome, int bi, int nif);
    std::string ObterNomePessoa(int bi) const;
    std::string obterLista() const;
    bool atualizarNomePessoa(int bi, const std::string &nome);
    int obterNumeroPessoa() const {return pessoas.size();}
    const Pessoa *obterPessoa(int bi) const;
    bool removerPessoa(int bi);
    bool tarsferirPessoa(int bi, Pais &paisDestino);

protected:
    void apagarTodasAsPessoas();
    bool adicionarPessoa(Pessoa *pessoa);

private:
    std::string nome;
    std::vector<Pessoa *> pessoas;
    auto procurarPessoa(int bi) const;

};


#endif //FICHA7_EX4_PAIS_H
