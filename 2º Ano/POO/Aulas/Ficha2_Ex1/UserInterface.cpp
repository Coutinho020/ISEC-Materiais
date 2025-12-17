#include "UserInterface.h"
#include <cctype>  // para isupper

using namespace std;

namespace UserInterface{

    bool dadosSaoValidos(string s){

        return !s.empty() && s[0] >= 'A' && s[0] <= 'Z';

        // s!.empty() ->se a string estiverr vazia;
        // isupper(s[0]) -> se o primeiro carater da string é maiuscula;
    }
}
