#ifndef FICHA7_EX3_AGENDA_H
#define FICHA7_EX3_AGENDA_H
#include <string>
#include "Contacto.h"
#include <map>

class Agenda {
public:
    bool insere(std::string nome, std::string morada, int tel);
    bool elimina(std::string nome);
    int obtemTelefone(std::string nome) const;
    std::string obtemMorada(std::string nome) const;
    bool atualizaTelefone(std::string nome, int tel);
    bool atualizaMorada(std::string nome, std::string morada);
    bool atualizaNome(std::string nomeAntigo, std::string nomeNovo);
    std::string obtemLista() const;
private:
    std::map<std::string, Contacto> contactos;

};



#endif //FICHA7_EX3_AGENDA_H
