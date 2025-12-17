#include "Valioso.h"
#include <stdexcept>

Valioso::Valioso() : valor(INT_MIN) {}

Valioso::Valioso(const std::string &descricao,int valor)
        : descricao(descricao), valor(valor) {
    if (valor <= 0)
        throw std::invalid_argument("Deve ter valor positivo");
}

int Valioso::obtemValor() const noexcept { return valor; }

std::string Valioso::obtemDescricao() const noexcept { return descricao; }

bool Valioso::semValor() const noexcept { return valor <= 0; }
