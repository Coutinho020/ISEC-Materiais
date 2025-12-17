#ifndef FICHA5_EX2_ARMARIOFICHAS_H
#define FICHA5_EX2_ARMARIOFICHAS_H
#include <string>
#include <initializer_list>

class ArmarioFichas {
    class Cliente { // representa um cliente do consultório
        std::string nome;
        int nif; // identifica um cliente de forma unívoca
        int numConsultas;
    public:
        Cliente(std::string _nome, int _nif) :
             nome(_nome), nif(_nif), numConsultas(0) {
            // assumir que já estão aqui as validações necessárias
     }
        std::string obtemNome() const { return nome; }
        int obtemNIF() const { return nif; }
        int obtemNumConsultas() const { return numConsultas; }
        void novaConsulta() { ++numConsultas; }
        std::string obtemDesc() const {
        return nome + " / " + std::to_string(nif) +
               " / " + std::to_string(numConsultas);
    }
};
public:
    ArmarioFichas();
    ArmarioFichas(const ArmarioFichas &outro);

    ArmarioFichas &operator=(ArmarioFichas outro);

    int getNrClientes() const {return nrClientes;}

    bool adicionarCliente(const std::string &nome, int Nif);
    bool removerCliente(int nif); //TODO: TPC
    bool acrescentarClientes(const ArmarioFichas &outro); //TODO: TPC
    bool verificarClientesIguais(const ArmarioFichas &outro); //TODO: TPC

    bool registaConsulta(int nif);

    void esvaziar();
    std::string getLista() const;

    ~ArmarioFichas();

struct InfoCliente{
    std::string nome;
    int nrConsultas;
    bool valido;

    InfoCliente(std::string _nome, int _nrConsultas, bool _valido) : nome(_nome), nrConsultas(_nrConsultas), valido(_valido){}
};

    InfoCliente getInfoCliente(int nif);

private:
    Cliente **clientes;
    int nrClientes;

    int procuraCliente(int nif) const;
};


#endif //FICHA5_EX2_ARMARIOFICHAS_H
