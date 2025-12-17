#ifndef POO_TP_POSICAO_H
#define POO_TP_POSICAO_H
#include <string>
#include <cctype>

class Posicao {
    int linhas;
    int colunas;

public:
        Posicao(int lin = -1, int col = -1);

        int getLinhas() const {return linhas;}
        int getColunas() const {return colunas;}

        void setPosicao(int lin, int col) {linhas = lin; colunas = col;}
        bool validaTamanho() const;
        static bool converteLetras(const std::string &pos, Posicao &saida);
        std::string converteCoordenadas() const;

};


#endif //POO_TP_POSICAO_H
