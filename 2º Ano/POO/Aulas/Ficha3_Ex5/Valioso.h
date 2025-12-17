#ifndef PREPF3E5_VALIOSO_H
#define PREPF3E5_VALIOSO_H
#include <string>


class Valioso {
public:
    Valioso();
    Valioso(const std::string &descricao,int valor);
    int obtemValor() const noexcept;
    std::string obtemDescricao() const noexcept;
    bool semValor() const noexcept;
private:
    std::string descricao;
    int valor;
};



#endif
