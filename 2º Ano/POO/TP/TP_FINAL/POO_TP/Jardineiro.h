#ifndef POO_TP_JARDINEIRO_H
#define POO_TP_JARDINEIRO_H
#include "Posicao.h"
#include "Inventario.h"
#include "Settings.h"

class Jardim;
class Celula;

class Jardineiro {
    Inventario inventario;
    Posicao pos;
    bool dentroDoJardim;

    int movimentosTurno;
    int entradasTurno;
    int saidasTurno;
    int plantacoesTurno;
    int colheitasTurno;
public:
    Jardineiro();

    //Posicao / Estado
    bool estaNoJardim() const {return dentroDoJardim;}
    Posicao getPos() const {return pos;}
    void resetTurno();

    //Movimento
    bool podeMover() const {return movimentosTurno < Settings::Jardineiro::max_movimentos;}
    bool move(char dir, const Jardim &j);

    //Entrar /Sair
    bool entra(const Posicao &p);
    bool podeEntrar() const {return entradasTurno < Settings::Jardineiro::max_entradas_saidas;}
    bool sai();
    bool podeSair() const {return saidasTurno < Settings::Jardineiro::max_entradas_saidas;}

    bool PegarFerramenta(int nrSerie);
    bool largarFerramenta();

    bool adicionarFerramenta(Ferramenta* f);
    Ferramenta* getFerramentaNaMao() const;
    bool usarFerramentaNaMao(Celula& c);
    void eliminarFerramentaNaMao();
    void resetUsoFerramentas();
    std::string descricaoInventario() const {return inventario.descricao();}

    bool podePlantar() const {return plantacoesTurno < Settings::Jardineiro::max_plantacoes;}
    void registaPlantacao() {++plantacoesTurno;}
    bool podeColher() const { return colheitasTurno < Settings::Jardineiro::max_colheitas;}
    void registaColheita() { ++colheitasTurno;}
};


#endif //POO_TP_JARDINEIRO_H
