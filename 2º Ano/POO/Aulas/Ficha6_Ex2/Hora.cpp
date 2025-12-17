#include <iostream>
#include "Hora.h"

using namespace std;

std::ostream  & operator << (std::ostream &os, const Hora &h){

    return os << "Horas: " << h.getHoras() << "h:" << h.getMinutos() << " min\n";
}

std::istream  & operator >> (std::istream &is, Hora &h){
    double hr, min;

    is >> hr >> min;

    h = Hora(hr, min);

    return is;
}