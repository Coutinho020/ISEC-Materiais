#ifndef FICHA6_EX5_TABELA_H
#define FICHA6_EX5_TABELA_H
#include <string>
#include <initializer_list>
#include <sstream>

class Tabela {
    static const unsigned int TAM = 10;
    int dados[TAM];
public:
    Tabela(int valor = 0) {
        for (unsigned int i = 0; i < TAM; ++i)
            dados[i] = valor;
    }

    Tabela(std::initializer_list<int> lista) {
        unsigned int i = 0;
        // assume que initializer list tem TAM elemnentos
        for (int valor : lista) // TPC: validar limites
            dados[i++] = valor;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "[";
        for (unsigned int i = 0; i < TAM; ++i) {
            oss << dados[i];
            if (i < TAM - 1) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    int &operator[](int i){
        if(i < 0 || i >= TAM)
            throw std::out_of_range("Index fora dos limites");
        return dados[i];
    }

    int operator () (int valor) const{
        int cont = 0;
        for(int i = 0; i < TAM; i++){
            if(dados[i] == valor)
                cont++;
        }
        return cont;
    }
};

#endif //FICHA6_EX5_TABELA_H
