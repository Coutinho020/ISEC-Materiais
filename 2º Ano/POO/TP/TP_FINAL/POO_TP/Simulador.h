#ifndef POO_TP_SIMULADOR_H
#define POO_TP_SIMULADOR_H
#include <fstream>
#include <map>
#include <string>
#include "Settings.h"
#include "Jardim.h"
#include "ComandoParser.h"

class Simulador {

public:
    Simulador();
    void lerComandos();
    void executa(const Comando &cmd);
    bool executaFicheiro(const std::string &nomeFicheiro);
    void avancaUmInstante();

private:
    Jardim jardim;
    ComandoParser parser;

    bool ativo;
    int instante;
    bool jardimInicializado;

    struct Snapshot {
        Jardim jardim;
        int instante;
        bool jardimInicializado;

        Snapshot() : instante(0), jardimInicializado(false) {}
        Snapshot(const Jardim& j, int inst, bool ini) : jardim(j), instante(inst), jardimInicializado(ini) {}
    };

    std::map<std::string, Snapshot> copias;
};


#endif //POO_TP_SIMULADOR_H
