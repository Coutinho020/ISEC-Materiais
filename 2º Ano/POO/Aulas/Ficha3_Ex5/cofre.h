#ifndef PREPF3E5_COFRE_H
#define PREPF3E5_COFRE_H
#include <string>
#include "Valioso.h"

class Cofre {
public:
    Cofre(unsigned int codigo);

    bool estaAberto() const noexcept;
    bool estaFechado() const noexcept;
    bool estaBloqueado() const noexcept;

    bool abre(unsigned int senha) noexcept;
    bool fecha() noexcept;

    bool colocar(const Valioso &item, unsigned int pos) ;
    Valioso retira(unsigned int pos) ;
    //bool retira(int pos, Valioso &item) ;
    std::string listarItens() const;



    bool alteraCodigo(unsigned int atualCodigo,unsigned int novoCodigo) ;
    bool desbloqueia(unsigned int superCodigo) ;

    static bool mudaSuperCodigo(unsigned int antigoSuperCodigo, unsigned int novoSuperCodigo) ;

private:
    static const int MAX_ITENS = 10;
    static const int MAX_TENTATIVAS = 3;
    static const unsigned int CODIGO_MIN = 1000;
    static const unsigned int CODIGO_MAX = 9999;
    static const unsigned int SUPER_CODIGO_MIN = 10000000;
    static const unsigned int SUPER_CODIGO_MAX = 99999999;

    static bool validaCodigo(unsigned int codigo);
    static bool validaSuperCodigo(unsigned int superCodigo);

    void resetMudanca();

    Valioso itens[MAX_ITENS];
    unsigned int codigo;
    bool aberto,bloqueado;
    unsigned int codigoEmAlteracao;
    int tentativas;

    static unsigned int superCodigo;
};


#endif
