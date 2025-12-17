#ifndef POO_TP_SIMULADOR_H
#define POO_TP_SIMULADOR_H
#include <fstream>
#include "Settings.h"
#include "Jardim.h"
#include "ComandoParser.h"
#include "Jardineiro.h"


class Simulador {

public:
    Simulador();
    void lerComandos();
    void executa(const Comando &cmd);
    bool executaFicheiro(const std::string &nomeFicheiro);

private:
    Jardim jardim;
    ComandoParser parser;

    bool ativo;
    int instante;
    bool jardimInicializado;
    void limpaContadoresAcao();

    int movimentos;
    int entradasEsaidas;
    int plantacoes;
    int colheitas;
};


#endif //POO_TP_SIMULADOR_H
