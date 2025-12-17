#include "Inventario.h"
#include <sstream>
#include <iostream>

using namespace std;

Inventario::Inventario() : nrFerramentas(0), naMao(nullptr) {

    for (int i = 0; i < MAX_Ferramentas; ++i) {
        ferramentas[i] = nullptr;
    }
}


int Inventario::procurar(int nrSerie) const {
    for (int i = 0; i < nrFerramentas; ++i) {
        if (ferramentas[i]->getNrSerie() == nrSerie) {
            return i;
        }
    }
    return -1;
}

const Ferramenta* Inventario::getFerramenta(int nrSerie) const {
    int index = procurar(nrSerie);
    if (index != -1) {
        return ferramentas[index];
    }
    return nullptr;
}

bool Inventario::adicionar(Ferramenta* f) {
    if (f == nullptr || nrFerramentas >= MAX_Ferramentas) {
        return false;
    }
    ferramentas[nrFerramentas] = f;
    nrFerramentas++;
    return true;
}

Ferramenta* Inventario::pegar(int nrSerie) {
    int index = procurar(nrSerie);
    if (index == -1) {
        return nullptr;
    }

    if (naMao) {
        largar();
    }

    naMao = ferramentas[index];

    if (index != nrFerramentas - 1) {
        ferramentas[index] = ferramentas[nrFerramentas - 1];
    }
    ferramentas[nrFerramentas - 1] = nullptr;
    nrFerramentas--;

    return naMao;
}

bool Inventario::largar() {
    if (naMao) {
        if (nrFerramentas < MAX_Ferramentas) {
            ferramentas[nrFerramentas] = naMao;
            nrFerramentas++;
            naMao = nullptr;
            return true;
        }
    }
    return false;
}


std::string Inventario::descricao() const {
    ostringstream oss;
    oss << "\n--- Inventario (" << nrFerramentas << "/" << MAX_Ferramentas << " itens em posse) ---\n";

    if (naMao) {
        oss << "Na Mao (ATIVA): " << naMao->descricao() << "\n";
    } else {
        oss << "Na Mao (ATIVA): Nenhuma.\n";
    }

    oss << "Em Posse:\n";
    if (nrFerramentas == 0) {
        oss << "  Vazio.\n";
    } else {
        for (int i = 0; i < nrFerramentas; ++i) {
            oss << "  " << ferramentas[i]->descricao() << "\n";
        }
    }

    return oss.str();
}