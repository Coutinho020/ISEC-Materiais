#include <stdio.h>
#include "ponto.h"
#include "retangulo.h"

int main(){

    ponto2D p1 = {3, -1}, p2;
    printPonto(p1);
   // initPonto(&p2);
   // printPonto(p2);
    movePonto(&p1, -4, -1);
    printPonto(p1);
    //printf("Quadrante deste ponto: %d\n", quadrante(p1));


   // ret r1 ={0, 0, 2, 3}, r2;
   // printRet(r1);
   // initRet(&r2);
    //printRet(r2);
    // printf("Area do retangulo: %d", areaR(r2));

  /*  int verificacao = dentroR(r1, p1);
    if(verificacao == 0){
        printf("O ponto esta fora do retangulo!!!!\n");
    }else{
        printf("O ponto esta dentro do retangulo!!!\n");
    }
*/
    return 0;
}
