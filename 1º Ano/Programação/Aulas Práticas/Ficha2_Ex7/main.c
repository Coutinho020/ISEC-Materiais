#include <stdio.h>
#include <string.h>

void MudaFrase(char fr[]) {

    int i = 0;

    while (fr[i] == ' ') {

        i++;

    }

    while(fr[i] != '\0'){

        if(fr[i] != ' '){

            printf("%c", fr[i]);
            i++;

        }else if(fr[i] == ' ' && fr[i-1] != ' '){

            printf("\n");
            i++;

        }else{

            i++;

        }
    }
}
int main(){

    char frase[] = "    Hoje e      Domingo!";

    MudaFrase(frase);

    return 0;
}
