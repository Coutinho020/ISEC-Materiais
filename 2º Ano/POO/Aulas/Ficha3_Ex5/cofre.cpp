#include "Cofre.h"

#include <iomanip>
#include <sstream>

using namespace std;

unsigned int Cofre::superCodigo = 12345678;

Cofre::Cofre(unsigned int codigo)
        :   codigo(codigo),aberto(false),bloqueado(false),
            tentativas(0),codigoEmAlteracao(CODIGO_MIN-1) {
    if (!validaCodigo(codigo)) {
        throw invalid_argument("Invalid initial code");
    }
    /*for (int i = 0; i < MAX_ITENS; i++) {
        itens[i] = Valioso();
    }*/
}

bool Cofre::estaAberto() const noexcept {
    return aberto;
}

bool Cofre::estaFechado() const noexcept {
    return !aberto;
}

bool Cofre::estaBloqueado() const noexcept {
    return bloqueado;
}

bool Cofre::abre(unsigned int senha) noexcept {
    resetMudanca();
    if (bloqueado) return false;
    if (aberto) return true;
    if (senha != codigo) {
        tentativas++;
        if (tentativas >= 3)
            bloqueado = true;
        return false;
    }
    tentativas = 0;
    aberto = true;
    return true;
}

bool Cofre::fecha() noexcept {
    resetMudanca();
    if (bloqueado)
        return false;
    aberto = false;
    return true;
}

bool Cofre::colocar(const Valioso &item, unsigned int pos) {
    resetMudanca();
    if (bloqueado || !aberto || pos < 1 || pos > MAX_ITENS || item.semValor() || !itens[pos-1].semValor())
        return false;
    itens[pos-1] = item;
    return true;
}

Valioso Cofre::retira(unsigned int pos) {
    resetMudanca();
    if (bloqueado || !aberto || pos < 1 || pos > MAX_ITENS || itens[pos-1].semValor())
        return {};
    Valioso ret = itens[pos-1];
    itens[pos-1] = Valioso();
    return ret;
}

/*bool Cofre::retira(unsigned int pos, Valioso &item) {
    resetMudanca();
    if (bloqueado || !aberto || pos < 1 || pos > MAX_ITENS || itens[pos-1].semValor())
        return false;
    item = itens[pos-1];
    itens[pos-1] = Valioso();
    return true;
}*/

std::string Cofre::listarItens() const {
    if (bloqueado || !aberto)
        return "";
    ostringstream oss;
    for (int i = 0; i < MAX_ITENS; i++) {
        if (!itens[i].semValor())
            oss << setw(2) << i+1 << " - " << itens[i].obtemDescricao() << " (" << itens[i].obtemValor() << ")" << endl;
    }
    return oss.str();
}

bool Cofre::alteraCodigo(unsigned int atualCodigo,unsigned int novoCodigo) {
    if (!aberto || bloqueado ||
        atualCodigo != codigo || novoCodigo==codigo ||
        !validaCodigo(novoCodigo)) {
        resetMudanca();
        return false;
    }

    if (!validaCodigo(codigoEmAlteracao))
        codigoEmAlteracao = novoCodigo;
    else if (codigoEmAlteracao != novoCodigo) {
        resetMudanca();
        return false;
    } else
        codigo = novoCodigo;
    return true;
}

bool Cofre::desbloqueia(unsigned int superCod) {
    resetMudanca();
    if (!bloqueado || superCodigo != superCod ) {
        return false;
    }
    bloqueado = false;
    tentativas = 0;
    return true;
}

bool Cofre::mudaSuperCodigo(unsigned int antigoSuperCodigo, unsigned int novoSuperCodigo) {
    if (antigoSuperCodigo!=superCodigo || !validaSuperCodigo(novoSuperCodigo))
        return false;
    superCodigo = novoSuperCodigo;
    return true;
}

bool Cofre::validaCodigo(unsigned int codigo) {
    return codigo >= CODIGO_MIN && codigo <= CODIGO_MAX;
}

bool Cofre::validaSuperCodigo(unsigned int superCodigo) {
    return superCodigo >= SUPER_CODIGO_MIN && superCodigo <= SUPER_CODIGO_MAX;
}

void Cofre::resetMudanca() {
    codigoEmAlteracao = CODIGO_MIN-1;
}
