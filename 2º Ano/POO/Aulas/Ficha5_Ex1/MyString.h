#ifndef FICHA5_EX1_MYSTRING_H
#define FICHA5_EX1_MYSTRING_H
#include <string>

class MyString {

public:
    MyString();
    MyString(const char *str);
    MyString(const MyString &outro);

    //MyString &operator=(const MyString &outro); //a=b=c;
    MyString &operator=(MyString outro);

    void acrescenta(const char *str);
    std::string obtemCString();

    bool removeDeAte(int i1, int i2);

    bool mudaCharAt(int i, char c);

    ~MyString();
private:
    char *dados;
    int tamanho;

    void copiaDados(const char *str);
};


#endif //FICHA5_EX1_MYSTRING_H
