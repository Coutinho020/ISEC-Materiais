#ifndef FICHA6_EX2_HORA_H
#define FICHA6_EX2_HORA_H
#include <string>
#include <sstream>
#include <iostream>

class Hora {
    unsigned int horas;
    unsigned int minutos;
    // Função auxiliar para formatar com 2 dígitos
    static std::string doisDigitos(unsigned int valor) {
        return (valor < 10 ? "0" : "") + std::to_string(valor);
    }

    void CorrigeValores(){
        int total = horas * 60 + minutos;
        minutos = total % 60;
        horas = (total / 60) % 24;
    }

public:
    // Tenta corrigir valores
    Hora(unsigned int h = 0, unsigned int m = 0) {
        minutos = m % 60;
        horas = (h + m / 60) % 24;
    }
    // Formato "hh:mm" com zeros à esquerda se necessário
    std::string getAsString() const {
        return doisDigitos(horas) + ":" + doisDigitos(minutos);
    }
    unsigned int getHoras() const { return horas; }
    unsigned int getMinutos() const { return minutos; }

    Hora &operator=(const Hora &h){
        if(this == &h)
            return *this;

        horas = h.horas;
        minutos = h.minutos;

        CorrigeValores();
        return *this;
    }

    Hora &operator+=(const Hora &h){
        horas += h.horas;
        minutos += h.minutos;
        CorrigeValores();

        return *this;
    }

    Hora &operator+=(int i){
        minutos += i;
        CorrigeValores();

        return *this;
    }

    explicit operator bool() const {
        return horas==0 && minutos==0;
        //return x!=0 || y!=0;
    }

    bool operator==(const Hora &h) const{
        return h.horas == horas  && h.minutos==minutos;
    }

    bool operator > (const Hora &h) const{
        if(horas > h.horas)
            return true;

        if(horas == h.horas && minutos > h.minutos)
            return true;

        return false;
    }

    operator int() const{
        return horas*60 + minutos;
    }

    Hora operator + (const Hora &h) {
        return Hora(*this) += h;
    }
};

std::ostream  & operator << (std::ostream &os, const Hora &h);

std::istream  & operator >> (std::istream &is, Hora &h);

#endif //FICHA6_EX2_HORA_H
