#ifndef POO_TP_COMANDOPARSER_H
#define POO_TP_COMANDOPARSER_H
#include "Comando.h"
#include "Posicao.h"
#include "Jardim.h"
#include <string>

class ComandoParser {

public:
    ComandoParser();
    // parse linha; se isInitialized for false, valida se é "jardim" ou "executa"
    Comando parse(const std::string& linha, const Jardim *jardim, bool estaInicializado) const;

private:
    static void trim(const std::string &in, std::string &out);
    static void divideEmTokens(const std::string &linha, std::string tokens[], int &nTokens);

    bool valorValido(const std::string &s) const;
    bool validaCoordenada(const std::string &s) const;
    bool comandoParaMover(const std::string &s) const;
    bool validaPlanta(const std::string &s) const;
    bool validaFerramenta(const std::string &s) const;
};


#endif //POO_TP_COMANDOPARSER_H
