#include "DataStore.h"

using namespace std;

namespace DataStore{

    bool dadosSaoValidos(string s){

        return s.length() >= 5 && s.length() <= 10;

    }
}
