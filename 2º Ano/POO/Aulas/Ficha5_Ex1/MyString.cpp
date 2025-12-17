#include "MyString.h"
#include <cstring>
#include <iostream>

using namespace std;

MyString::MyString() : tamanho(0), dados(new char[1]){
    cout << "MyString()" << endl;
    dados[0] = '\0';
}

MyString::MyString(const char *str) {
    cout << "MyString(const char *str)" << endl;
    copiaDados(str);
}

MyString::MyString(const MyString &outro){
    cout << "MyString(const MyString &outro)" << endl;
    copiaDados(outro.dados);
    //*this = outro;
}

void MyString::copiaDados(const char *str) {
    if(str == nullptr){
        tamanho = 0;
        dados = new char[1];
        dados[0] = '\0';
        return;
    }
    tamanho = strlen(str);
    dados = new char[tamanho + 1];
    strcpy(dados, str);
}

MyString::~MyString() {
    delete[] dados;
}

void MyString::acrescenta(const char *str) {
    tamanho += ::strlen(str);
    char *novoDados = new char[tamanho + 1];
    strcpy(novoDados, dados);
    strcat(novoDados, str);
    delete[] dados;
    dados = novoDados;
}

std::string MyString::obtemCString() {
    return string(dados);
}

bool MyString::mudaCharAt(int i, char c) {
    if(i < 0 || i >= tamanho)
        return false;

    dados[i] = c;
    return true;
}

bool MyString::removeDeAte(int i1, int i2) {
    if(i1 < 0 || i1 >= tamanho || i2 < i1 || i2 >=tamanho)
        return false;

    int tam = tamanho - (i2 - i1) + 1;
    char *novoDados = new char[tam + 1];

    int k = 0;
    for(int i = 0; i < tamanho; i++) {
        if(i < i1 || i > i2){
            novoDados[k] = dados[i];
            k++;
        }
    }
    delete [] dados;
    dados = novoDados;
    tamanho = tam;
    return true;
}

/*MyString &MyString::operator=(const MyString &outro) {
    cout << "MyString::operator= " << endl;
    if(this == &outro)
        return *this;

    delete[] dados;
    copiaDados(outro.dados);
    return *this;
}*/

MyString &MyString::operator=(MyString outro){
    swap(dados, outro.dados);
    swap(tamanho, outro.tamanho);
    return *this;
}