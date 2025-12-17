#ifndef FICHA3_EX6_MSG_H
#define FICHA3_EX6_MSG_H
#include <string>
#include <sstream>

class MSG {

public:
    MSG(char l = 'x');

    std::string getDados() const;

    ~MSG();
private:
    char letra;
    const int numero;
    static int contador;
};


#endif //FICHA3_EX6_MSG_H
