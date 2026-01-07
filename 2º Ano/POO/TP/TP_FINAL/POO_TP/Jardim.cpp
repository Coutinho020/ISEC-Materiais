#include "Jardim.h"
#include "Cacto.h"
#include "Roseira.h"
#include "ErvaDaninha.h"
#include "PlantaExotica.h"
#include "Regador.h"
#include "SuplementoNatural.h"
#include "Tesoura.h"
#include "Adubo.h"
#include <sstream>

using namespace std;

Jardim::Jardim() : lins(0), cols(0), celulas(nullptr){

}

Jardim::Jardim(const Jardim& outro) : lins(0), cols(0), celulas(nullptr) {
    copia(outro);
}

Jardim& Jardim::operator=(const Jardim& outro) {
    if (this != &outro) {
        libertarMemoria();
        copia(outro);
    }
    return *this;
}

void Jardim::copia(const Jardim &outro) {
    lins = outro.lins;
    cols = outro.cols;

    if (outro.celulas == nullptr) {
        celulas = nullptr;
        jardineiro = outro.jardineiro;
        return;
    }

    celulas = new Celula[lins * cols];

    for (int i = 0; i < lins * cols; i++) {

        celulas[i].setSolo(outro.celulas[i].getSolo());

        if (outro.celulas[i].getPlanta() != nullptr) {
            celulas[i].colocarPlanta(outro.celulas[i].getPlanta()->clone());
        }

        if (outro.celulas[i].getFerramenta() != nullptr) {
            celulas[i].colocarFerramenta(outro.celulas[i].getFerramenta()->clone());
        }
    }

    jardineiro = outro.jardineiro;
}

void Jardim::libertarMemoria() {
    if (celulas == nullptr)
        return;

    for (int i = 0; i < lins * cols; i++) {
        if (celulas[i].getPlanta() != nullptr) {
            delete celulas[i].removerPlanta();
        }
        if (celulas[i].getFerramenta() != nullptr) {
            delete celulas[i].removerFerramenta();
        }
    }

    delete[] celulas;
    celulas = nullptr;
}


Jardim::~Jardim(){

    libertarMemoria();
}

bool Jardim::inicializa(int l, int c) {

    if(l <= 0 || c <= 0 || l > MAX_LINS || c > MAX_COLS)
        return false;

    libertarMemoria();

    lins = l;
    cols = c;
    celulas = new Celula[lins * cols];

    for (int i = 0; i < 3; i++) {
        colocaFerramentaAleatoria();
    }
    return true;
}

Celula &Jardim::aceder(int l, int c) {
    return celulas[index(l, c)];
}

bool Jardim::PosicaoValida(int l, int c) const {
    return l >= 0 && l < lins && c >= 0 && c < cols;
}

void Jardim::print() const {
    if(celulas == nullptr) {
        cout << "(jardim nao criado)\n";
        return;
    }

    cout << "  ";

    for(int c = 0; c < cols; c++)
        cout << char('A' + c) << " ";
    cout << "\n";

    for(int l = 0; l < lins; l++){
        cout << char('A' + l) << " ";
        for(int c = 0 ; c < cols; c++){
            if(jardineiro.estaNoJardim() && jardineiro.getPos().getLinhas() == l && jardineiro.getPos().getColunas() == c){
                cout << "*" << " ";
            }else{
                cout << celulas[index(l,c)].simbolo() << " ";
            }
        }
        cout << "\n";
    }
}

Posicao Jardim::geraPosicaoAleatoria() const {
    int l = rand() % lins;
    int c = rand() % cols;
    return Posicao(l, c);
}

bool Jardim::adicionarPlanta(const Posicao &p, char tipo) {

    int l = p.getLinhas();
    int c = p.getColunas();

    if(!PosicaoValida(l, c) || !jardineiro.podePlantar())
        return false;

    Celula &cel = aceder(l, c);
    if(cel.getPlanta() != nullptr)
        return false;

    Planta *nova = nullptr;
    switch (tipo) {
        case 'c': nova = new Cacto(); break;
        case 'r': nova = new Roseira(); break;
        case 'e': nova = new ErvaDaninha(); break;
        case 'x': nova = new PlantaExotica(); break;
        default:
            return false;
    }
    cel.colocarPlanta(nova);
    jardineiro.registaPlantacao();
    verificarRoseirasVizinhanca(l, c);
    return true;
}

bool Jardim::removerPlanta(const Posicao &p) {

    int l = p.getLinhas();
    int c = p.getColunas();

    if(!PosicaoValida(l, c) || !jardineiro.podeColher())
        return false;

    Celula &cel = aceder(l, c);
    if(cel.getPlanta() == nullptr)
        return false;

    delete cel.removerPlanta();
    jardineiro.registaColheita();
    return true;
}

bool Jardim::adicionarFerramenta(const Posicao &p, Ferramenta *f) {

    int l = p.getLinhas();
    int c = p.getColunas();

    if(!PosicaoValida(l, c))
        return false;

    Celula &cel = aceder(l, c);
    if(cel.getFerramenta() != nullptr)
        return false;

    cel.colocarFerramenta(f);
    return true;
}

Ferramenta *Jardim::criarFerramenta(char tipo) const {
    switch (tipo) {
        case 'g': return new Regador();
        case 'a': return new Adubo();
        case 't': return new Tesoura();
        case 'z': return new SuplementoNatural();
        default:
            return nullptr;
    }
}

Ferramenta* Jardim::criaFerramentaAleatoria() const {

    int tipo = rand() % 4;
    switch (tipo) {
        case 0: return new Regador();
        case 1: return new Adubo();
        case 2: return new Tesoura();
        case 3: return new SuplementoNatural();
    }
    return nullptr;
}

void Jardim::colocaFerramentaAleatoria() {

    while (true) {
        Posicao p = geraPosicaoAleatoria();
        Celula &cel = aceder(p.getLinhas(), p.getColunas());

        if (cel.getFerramenta() == nullptr) {
            Ferramenta *f = criaFerramentaAleatoria();
            cel.colocarFerramenta(f);
            return;
        }
    }
}

void Jardim::recolherFerramentaSeExistir() {

    if (!jardineiro.estaNoJardim())
        return;

    int l = jardineiro.getPos().getLinhas();
    int c = jardineiro.getPos().getColunas();

    Celula &cel = aceder(l, c);
    if(cel.getFerramenta() == nullptr)
        return;

    Ferramenta* f = cel.removerFerramenta();
    jardineiro.adicionarFerramenta(f);

    colocaFerramentaAleatoria();
}

void Jardim::tentarUsarFerramenta() {
    if(!jardineiro.estaNoJardim())
        return;

    Celula &cel = aceder(jardineiro.getPos().getLinhas(), jardineiro.getPos().getColunas());
    jardineiro.usarFerramentaNaMao(cel);
}

bool Jardim::moverJardineiro(char dir) {
    if(!jardineiro.move(dir, *this))
        return false;

    recolherFerramentaSeExistir();
    tentarUsarFerramenta();
    return true;
}

bool Jardim::entraJardineiro(const Posicao &p) {
    if (!PosicaoValida(p.getLinhas(), p.getColunas()))
        return false;

    if (!jardineiro.entra(p))
        return false;

    recolherFerramentaSeExistir();
    tentarUsarFerramenta();
    return true;
}

bool Jardim::saiJardineiro() {
    return jardineiro.sai();
}

void Jardim::avancaInstante() {
    if(celulas == nullptr)
        return;

    for(int l = 0; l < lins; l++){
        for(int c = 0; c < cols; c++){
            Celula &cel = aceder(l,c);
            Planta *pl = cel.getPlanta();

            if(pl != nullptr){
                pl->processaInstante(cel);

                if(!pl->estaViva()){
                    delete cel.removerPlanta();
                }
                else{
                    if(pl->getSimbolo() == 'r'){
                        if(roseiraRodeada(l,c)){
                            cel.adicionarAguaSolo(pl->getAgua() / 2);
                            cel.adicionarNutrientesSolo(pl->getNutrientes() / 2);
                            delete cel.removerPlanta();
                        }
                    }
                }
            }
        }
    }

    for (int l = 0; l < lins; l++) {
        for (int c = 0; c < cols; c++) {

            Celula &cel = aceder(l, c);
            Planta *pl = cel.getPlanta();

            if (pl != nullptr && pl->querMultiplicar()) {
                tentarMultiplicar(l, c, pl);
                pl->resetMultiplicacao();
            }
        }
    }

    jardineiro.resetTurno();
    jardineiro.resetUsoFerramentas();
    if(jardineiro.estaNoJardim()){
        tentarUsarFerramenta();
    }
}

std::string Jardim::listarPlantas() const {
    ostringstream oss;
    oss << "--- Lista de Plantas ---\n";

    bool encontrou = false;

    for (int l = 0; l < lins; l++) {
        for (int c = 0; c < cols; c++) {
            const Celula& cel = celulas[index(l, c)];
            Planta* pl = cel.getPlanta();

            if (pl) {
                Posicao p(l, c);
                oss << p.converteCoordenadas() << " : " << pl->descricao() << "\n";
                encontrou = true;
            }
        }
    }
    if (!encontrou)
        oss << "(nenhuma planta no jardim)\n";

    return oss.str();
}

std::string Jardim::listarPlanta(const Posicao &p) const {
    ostringstream oss;

    int l = p.getLinhas();
    int c = p.getColunas();

    if (!PosicaoValida(l, c)) {
        oss << "[ERRO] Posicao invalida\n";
        return oss.str();
    }

    const Celula cel = acederC(l, c);
    Planta* pl = cel.getPlanta();

    if (!pl) {
        oss << "Nao existe planta na posicao " << p.converteCoordenadas() << "\n";
        return oss.str();
    }

    oss << "--- Planta em " << p.converteCoordenadas() << " ---\n";
    oss << pl->descricao() << "\n";

    return oss.str();
}

std::string Jardim::listarArea() const {
    std::ostringstream oss;
    oss << "--- Area do Jardim ---\n";

    bool encontrou = false;

    for (int l = 0; l < lins; l++) {
        for (int c = 0; c < cols; c++) {
            const Celula cel = acederC(l, c);

            if (cel.getPlanta() || cel.getFerramenta()) {
                Posicao p(l, c);
                oss << p.converteCoordenadas() << " : ";

                if (cel.getPlanta())
                    oss << cel.getPlanta()->descricao() << " ";

                if (cel.getFerramenta())
                    oss << cel.getFerramenta()->descricao() << " ";

                oss << "| Solo: " << cel.descricaoSolo() << "\n";
                encontrou = true;
            }
        }
    }
    if (!encontrou)
        oss << "(area totalmente vazia)\n";

    return oss.str();
}

std::string Jardim::listarSolo(const Posicao &centro, int raio) const {
    ostringstream oss;

    int l0 = centro.getLinhas();
    int c0 = centro.getColunas();

    if (!PosicaoValida(l0, c0)) {
        oss << "[ERRO] Posicao invalida\n";
        return oss.str();
    }

    oss << "--- Solo (raio " << raio << ") ---\n";

    for (int l = l0 - raio; l <= l0 + raio; l++) {
        for (int c = c0 - raio; c <= c0 + raio; c++) {
            if (PosicaoValida(l, c)) {
                const Celula cel = acederC(l, c);
                Posicao p(l, c);

                oss << p.converteCoordenadas()
                    << " : Solo(" << cel.descricaoSolo() << ")";

                if (cel.getPlanta())
                    oss << " | Planta: " << cel.getPlanta()->getNome();

                if (cel.getFerramenta())
                    oss << " | Ferramenta: " << cel.getFerramenta()->getNome();

                oss << "\n";
            }
        }
    }

    return oss.str();
}

bool Jardim::jardineiroLargaFerramenta() {
    return jardineiro.largarFerramenta();
}

bool Jardim::jardineiroPegaFerramenta(int nrSerie) {
    bool ok = jardineiro.PegarFerramenta(nrSerie);
    if(ok){
        tentarUsarFerramenta();
    }
    return ok;
}

bool Jardim::jardineiroCompraFerramenta(char tipo) {
    Ferramenta *f = criarFerramenta(tipo);
    if(f == nullptr)
        return false;

    if(!jardineiro.adicionarFerramenta(f)){
        delete f;
        return false;
    }
        return true;
}

std::string Jardim::listarFerramentasJardineiro() const {
    return jardineiro.descricaoInventario();
}

void Jardim::tentarMultiplicar(int l, int c, Planta *p) {

    int dl[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    bool tentado[4] = {false, false, false, false};
    int tentativas = 0;

    while (tentativas < 4) {

        int i = rand() % 4;

        if (tentado[i] == false) {
            tentado[i] = true;
            tentativas++;

            int nl = l + dl[i];
            int nc = c + dc[i];

            if (PosicaoValida(nl, nc)) {

               Celula &viz = aceder(nl, nc);

               if(p->getSimbolo() == 'e'){

                   Planta *nova = p->multiplicar();

                   if(nova != nullptr){
                       if(viz.getPlanta() != nullptr){
                           delete viz.removerPlanta();
                       }
                       viz.colocarPlanta(nova);
                       return;
                   }
               }else{
                   if(viz.getPlanta() == nullptr){
                       Planta *nova = p->multiplicar();

                       if(nova != nullptr){
                           viz.colocarPlanta(nova);
                           return;
                       }
                   }
               }
            }
        }
    }
}

bool Jardim::roseiraRodeada(int l, int c) const {
    const int dl[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    int vizinhosValidos = 0;
    int vizinhosComPlanta = 0;

    for (int i = 0; i < 4; i++) {
        int nl = l + dl[i];
        int nc = c + dc[i];

        if (PosicaoValida(nl, nc)) {
            vizinhosValidos++;

            if (acederC(nl, nc).getPlanta() != nullptr)
                vizinhosComPlanta++;
        }
    }

    return vizinhosValidos > 0 && vizinhosComPlanta == vizinhosValidos;
}

void Jardim::verificarERemoverRoseiraSeRodeada(int l, int c) {
    if (!PosicaoValida(l, c))
        return;

    Celula &cel = aceder(l, c);
    Planta *p = cel.getPlanta();

    if (p != nullptr && p->getSimbolo() == 'r') {
        if (roseiraRodeada(l, c)) {
            // comportamento de morte da roseira: devolve metade ao solo
            cel.adicionarAguaSolo(p->getAgua() / 2);
            cel.adicionarNutrientesSolo(p->getNutrientes() / 2);
            delete cel.removerPlanta();
        }
    }
}

void Jardim::verificarRoseirasVizinhanca(int l, int c) {
    const int dl[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nl = l + dl[i];
        int nc = c + dc[i];
        verificarERemoverRoseiraSeRodeada(nl, nc);
    }
}







