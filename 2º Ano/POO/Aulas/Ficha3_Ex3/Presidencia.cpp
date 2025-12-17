#include <iostream>
#include <sstream>
#include "Presidencia.h"

using namespace std;

// Construtor com pessoas já criadas
Presidencia::Presidencia(const Pessoa &p, const Pessoa &v,const Pessoa &s) :
        presidente(p), vice(v), secretario(s){

}

// Construtor com dados diretos
Presidencia::Presidencia(const string PresidenteNome, const string PresidenteId, const int PresidenteIdade,
                         const string ViceNome, const string ViceId, const int ViceIdade,
                         const string SecretarioNome, const string SecretarioId, const int SecretarioIdade)
        : presidente(PresidenteNome, PresidenteId, PresidenteIdade),
          vice(ViceNome, ViceId, ViceIdade),
          secretario(SecretarioNome, SecretarioId, SecretarioIdade)
{


}
