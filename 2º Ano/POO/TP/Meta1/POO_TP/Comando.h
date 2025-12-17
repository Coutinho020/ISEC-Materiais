#ifndef POO_TP_COMANDO_H
#define POO_TP_COMANDO_H
#include <string>

class ComandoTipo {

public:
    static const int CMD_INVALID = 0;
    static const int CMD_JARDIM  = 1;
    static const int CMD_AVANCA  = 2;
    static const int CMD_PLANTA  = 3;
    static const int CMD_COLHE   = 4;
    static const int CMD_LARGA   = 5;
    static const int CMD_PEGA    = 6;
    static const int CMD_MOVE    = 7;
    static const int CMD_ENTRA   = 8;
    static const int CMD_SAI     = 9;
    static const int CMD_GRAVA   = 10;
    static const int CMD_RECUPERA= 11;
    static const int CMD_APAGA   = 12;
    static const int CMD_EXECUTA = 13;
    static const int CMD_FIM     = 14;
    static const int CMD_LAREA   = 15;
    static const int CMD_COMPRA  = 16;
    static const int CMD_LPLANTA = 17;
    static const int CMD_LPLANTAS= 18;
    static const int CMD_LSOLO   = 19;
    static const int CMD_LFERR   = 20;
};

struct Comando {
    int tipo;
    std::string tokens[8];
    int numTokens;
    std::string erro;

    Comando() : tipo(ComandoTipo::CMD_INVALID), numTokens(0), erro(""){}
};

#endif //POO_TP_COMANDO_H
