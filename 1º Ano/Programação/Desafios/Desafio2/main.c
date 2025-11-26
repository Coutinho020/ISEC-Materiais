#include <stdio.h>
#include "funcao.h"


int main() {

    projeto tab[4] = {{{12,2,2024}, {20,2,2024}, 0, {"obra", "cimento", "cal", "areia"} ,0},
                      {{20,4,2024}, {18,6,2024}, 0, {"papel", "tinta", "caneta", "ar"}, 0},
                      {{31,7,2024}, {1,8,2024}, 0, {"cal", "pregos", "fio", "alicate"}, 0},
                      {{1,1,2024}, {1,2,2024}, 0, {"pbx", "madeira", "ferro", "a345a"} ,0}};


    desafio2(tab, 4);

    mostraTab(tab, 4);

    return 0;
}
