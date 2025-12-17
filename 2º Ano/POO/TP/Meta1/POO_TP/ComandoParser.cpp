#include "ComandoParser.h"
#include <cctype>

using namespace std;

ComandoParser::ComandoParser(){}

void ComandoParser::trim(const string &in, string &out) {

    int inicio = 0;
    int fim = in.length();

    for (; inicio < fim && isspace(in[inicio]); ++inicio);
    for (; fim > inicio && isspace(in[fim - 1]); --fim);

    out = in.substr(inicio, fim - inicio);
}

void ComandoParser::divideEmTokens(const string &linha, string tokens[], int &nTokens) {

    nTokens = 0;
    string str = "";

    for(size_t i = 0; i <= linha.length(); i++){
        if(i == linha.length() || isspace(linha[i])){
            if(str.length() > 0){
                if(nTokens < 8){
                    tokens[nTokens] = str;
                    nTokens++;
                }
                str = "";
            }
        } else {
            str = str + linha[i];
        }
    }
}

bool ComandoParser::valorValido(const string &s) const{

    if(s.empty())
        return false;

    for(int i = 0; i < s.length(); i++)
        if(!isdigit(s[i]))
            return false;

    if(s.length() == 1 && s[0] == '0')
        return false;

    return true;
}

bool ComandoParser::validaCoordenada(const string &s) const{

    if(s.length() != 2)
        return false;

    if(s[0] < 'a' || s[0] > 'z')
        return false;

    if(s[1] < 'a' || s[1] > 'z')
        return false;

    return true;
}

bool ComandoParser::comandoParaMover(const string &s) const{

    if(s.length() != 1)
        return false;

    char c = s[0];

    return (c == 'e' || c == 'd' || c == 'c' || c == 'b');
}

bool ComandoParser::validaPlanta(const string &s) const{

    if(s.empty())
        return false;

    char c = s[0];

    return (c == 'c' || c == 'r' || c == 'e' || c == 'x');
}

bool ComandoParser::validaFerramenta(const string &s) const{

    if(s.empty())
        return false;

    char c = s[0];

    return (c == 'g' || c == 'a' || c == 't' || c == 'z');
}

Comando ComandoParser::parse(const string &linha, const Jardim *jardim, bool estaInicializado) const {

    Comando cmd;
    string s;
    trim(linha, s);

    if (s.empty()) {
        cmd.tipo = ComandoTipo::CMD_INVALID;
        cmd.erro = "Linha vazia";
        return cmd;
    }

    divideEmTokens(s, cmd.tokens, cmd.numTokens);

    if (cmd.numTokens == 0) {
        cmd.tipo = ComandoTipo::CMD_INVALID;
        cmd.erro = "Linha vazia";
        return cmd;
    }

    string prefixo = cmd.tokens[0];

    // Regra 1: Se Jardim NÃO está inicializado, SÓ aceita 'jardim' ou 'executa'
    if (!estaInicializado) {
        if (prefixo != "jardim" && prefixo != "executa") {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "O comando 'jardim' deve ser o primeiro comando (exceto 'executa').";
            return cmd;
        }
    }

    // Regra 2: Se Jardim JÁ está inicializado, NÃO aceita 'jardim' novamente
    if (estaInicializado && prefixo == "jardim") {
        cmd.tipo = ComandoTipo::CMD_INVALID;
        cmd.erro = "O comando 'jardim' so pode ser utilizado uma unica vez.";
        return cmd;
    }

    if (prefixo == "jardim") {
        cmd.tipo = ComandoTipo::CMD_JARDIM;

        if (cmd.numTokens != 3 || !valorValido(cmd.tokens[1]) || !valorValido(cmd.tokens[2])) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: jardim <Linhas> <Colunas>";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "avanca") {
        cmd.tipo = ComandoTipo::CMD_AVANCA;

        if (cmd.numTokens == 1)
            return cmd;
        if (cmd.numTokens == 2 && valorValido(cmd.tokens[1])) {
            return cmd;
        }
        cmd.tipo = ComandoTipo::CMD_INVALID;
        cmd.erro = "Sintaxe: avanca [n] (n inteiro positivo)";
        return cmd;
    }

    if (cmd.numTokens == 1 && comandoParaMover(cmd.tokens[0])) {
        cmd.tipo = ComandoTipo::CMD_MOVE;
        return cmd;
    }

    if (prefixo == "lplantas") {
        cmd.tipo = ComandoTipo::CMD_LPLANTAS;

        if (cmd.numTokens != 1) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: lplantas (sem argumentos adicionais)";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "lplanta") {
        cmd.tipo = ComandoTipo::CMD_LPLANTA;

        if (cmd.numTokens != 2 || !validaCoordenada(cmd.tokens[1])) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: lplanta lc";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "larea") {
        cmd.tipo = ComandoTipo::CMD_LAREA;

        if (cmd.numTokens != 1) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: larea (sem argumentos adicionais)";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "lsolo") {
        cmd.tipo = ComandoTipo::CMD_LSOLO;

        if (cmd.numTokens == 2 && validaCoordenada(cmd.tokens[1]))
            return cmd;
        if (cmd.numTokens == 3 && validaCoordenada(cmd.tokens[1]) && valorValido(cmd.tokens[2]))
            return cmd;
        cmd.tipo = ComandoTipo::CMD_INVALID;
        cmd.erro = "Sintaxe: lsolo lc [n] (n inteiro positivo)";
        return cmd;
    }

    if (prefixo == "lferr") {
        cmd.tipo = ComandoTipo::CMD_LFERR;

        if (cmd.numTokens != 1) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: lferr (sem argumentos adicionais)";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "colhe") {
        cmd.tipo = ComandoTipo::CMD_COLHE;

        if (cmd.numTokens != 2 || !validaCoordenada(cmd.tokens[1])) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: colhe lc";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "planta") {
        cmd.tipo = ComandoTipo::CMD_PLANTA;

        if (cmd.numTokens != 3 || !validaCoordenada(cmd.tokens[1]) || !validaPlanta(cmd.tokens[2])) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: planta lc <tipo de planta>";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "larga") {
        cmd.tipo = ComandoTipo::CMD_LARGA;

        if (cmd.numTokens != 1) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: larga (sem argumentos adicionais)";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "pega") {
        cmd.tipo = ComandoTipo::CMD_PEGA;

        if (cmd.numTokens == 2 && valorValido(cmd.tokens[1])) {
            return cmd;
        }
        cmd.tipo = ComandoTipo::CMD_INVALID;
        cmd.erro = "Sintaxe: pega n (sendo n o nr de serie da ferramenta)";
        return cmd;
    }

    if (prefixo == "compra") {
        cmd.tipo = ComandoTipo::CMD_COMPRA;

        if (cmd.numTokens != 2 || !validaFerramenta(cmd.tokens[1])) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: compra <tipo de ferramenta>";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "entra") {
        cmd.tipo = ComandoTipo::CMD_ENTRA;

        if (cmd.numTokens != 2 || !validaCoordenada(cmd.tokens[1])) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: entra lc";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "sai") {
        cmd.tipo = ComandoTipo::CMD_SAI;

        if (cmd.numTokens != 1) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: sai (sem argumentos adicionais)";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "grava") {
        cmd.tipo = ComandoTipo::CMD_GRAVA;

        if (cmd.numTokens != 2) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: grava nomeFicheiro";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "recupera") {
        cmd.tipo = ComandoTipo::CMD_RECUPERA;

        if (cmd.numTokens != 2) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: recupera nomeFicheiro";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "apaga") {
        cmd.tipo = ComandoTipo::CMD_APAGA;

        if (cmd.numTokens != 2) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: apaga nomeFicheiro";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "executa") {
        cmd.tipo = ComandoTipo::CMD_EXECUTA;

        if (cmd.numTokens != 2) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: executa nomeFicheiro";
            return cmd;
        }
        return cmd;
    }

    if (prefixo == "fim") {
        cmd.tipo = ComandoTipo::CMD_FIM;

        if (cmd.numTokens != 1) {
            cmd.tipo = ComandoTipo::CMD_INVALID;
            cmd.erro = "Sintaxe: fim (sem argumentos adicionais)";
            return cmd;
        }
        return cmd;
    }

    cmd.tipo = ComandoTipo::CMD_INVALID;
    cmd.erro = "Comando desconhecido: " + prefixo;
    return cmd;
}


