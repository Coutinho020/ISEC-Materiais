#ifndef POO_TP_JARDIM_H
#define POO_TP_JARDIM_H
#include <iostream>
#include "Celula.h"
#include "Jardineiro.h"
#include "Planta.h"
#include "Ferramenta.h"
#include "Posicao.h"

const int MAX_LINS = 26;
const int MAX_COLS = 26;

class Jardim {
    int lins;
    int cols;
    Celula* celulas;
    Jardineiro jardineiro;

    int index(int l, int c) const {return l * cols + c;}
    Celula& aceder(int l, int c);

    void libertarMemoria();
    void copia(const Jardim &outro);

    void tentarMultiplicar(int l, int c, Planta *p);
public:
    Jardim();
    Jardim(const Jardim &outro);

    ~Jardim();

    Jardim& operator=(const Jardim &outro);

    const Celula &acederC(int l, int c) const {return celulas[index(l, c)];}
    //Inicialização
    bool inicializa(int l, int c);

    //Tamanho do jardim
    int getLinhas() const{return lins;}
    int getCols() const {return cols;}

    bool PosicaoValida(int l, int c) const;
    Posicao geraPosicaoAleatoria() const;

    //Visualizaçãop
    void print() const;

    //Jardineiro
    const Jardineiro& getJardineiro() const { return jardineiro; }
    bool jardineiroLargaFerramenta();
    bool jardineiroPegaFerramenta(int nrSerie);
    bool jardineiroCompraFerramenta(char tipo);
    std::string listarFerramentasJardineiro() const;

    //Planta
    bool adicionarPlanta(const Posicao &p, char tipo);
    bool removerPlanta(const Posicao& p);
    bool roseiraRodeada(int l, int c) const;
    void verificarERemoverRoseiraSeRodeada(int l, int c);
    void verificarRoseirasVizinhanca(int l, int c);

    //moves
    bool moverJardineiro(char dir);
    bool entraJardineiro(const Posicao &p);
    bool saiJardineiro();
    void tentarUsarFerramenta();

    void avancaInstante();

    //Listagens
    std::string listarPlantas() const;
    std::string listarPlanta(const Posicao &p) const;
    std::string listarArea() const;
    std::string listarSolo(const Posicao &centro, int raio) const;

    //Ferramentas
    bool adicionarFerramenta(const Posicao &p, Ferramenta *f);
    Ferramenta* criarFerramenta(char tipo) const;
    Ferramenta* criaFerramentaAleatoria() const;
    void colocaFerramentaAleatoria();
    void recolherFerramentaSeExistir();
};


#endif //POO_TP_JARDIM_H
