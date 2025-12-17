#ifndef FICHA3_EX3_PRESIDENCIA_H
#define FICHA3_EX3_PRESIDENCIA_H
#include "Pessoa.h"


class Presidencia {
public:
    Presidencia(const Pessoa &presidente, const Pessoa &vice, const Pessoa &secretario);

    Presidencia(const std::string PresidenteNome, const std::string PresidenteId, const int PresidenteIdade,
                 const std::string ViceNome, const std::string ViceId, const int ViceIdade,
                 const std::string SecretarioNome, const std::string SecretarioId, const int SecretarioIdade);
private:
    Pessoa presidente, vice, secretario;
};


#endif //FICHA3_EX3_PRESIDENCIA_H
